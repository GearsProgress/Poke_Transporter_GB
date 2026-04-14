--- PTGB Link Debug Helper
---
--- This Lua script is designed to connect PTGB to Gen 1/2 on mGBA.
--- It requires a development build of mGBA.
---
--- How to use:
---  1. Load PTGB in mGBA
---  2. Tools -> Scripting -> Load script, select this file.
---  3. Check that it says "PTGB Link Debug Script", otherwise your mGBA may lack Lua support
---  4. Repeat, but for the Gen 1/2 game.
---
--- Most of the code is adapted from the demo scripts provided with mGBA.


console:log("-- PTGB Link Debug Script --")

-- Version check. The latest release as of writing is 0.10.5, which lacks watchpoint support. --
if C.WATCHPOINT_TYPE == nil then
    console:error("This script requires a more recent build of mGBA!")
    console:log("You can get a development build at https://mgba.io/downloads.html#development-downloads")
    console:log("If you want to build from source, remember to pass -DENABLE_SCRIPTING=1 to CMake.")
    return
end

-- Reentrancy check
--
-- If you load a script twice, mGBA will execute the script in the same environment
-- which causes "address in use" errors.
--
-- Requires a development build of mGBA, as watchpoints are a new feature.
if _G["PTGB_REENTRANCY_TEST"] then
    Stop()
end
_G["PTGB_REENTRANCY_TEST"] = true

--[[
    PTGB in Debug mode uses the following protocol, since mGBA doesn't let us write to REG_SIOCNT properly.

    1. PTGB will write a value to link_debug.output_byte
    2. PTGB will write true to link_debug.has_output
    3. The Lua script will detect this write via a watchpoint and send the byte to the GB part of the script
    4. PTGB will wait on link_debug.has_input
    5. When the Lua script receives a response, it will write the value to link_debug.input_byte, and write true
    to link_debug.has_input.
]]--


-- Let users know the script is working --
console:log("Make sure you enable [insert option here] in the Debug Menu")
console:log("If you would like to log the sent bytes, type EnableOutput(\"filename\") in the console and hit Run")
-- Port used for the socket. Chosen at random.

PORT = 31415
server = nil
sock = nil
watchpoint = -1
defer_watchpoint = -1
output_file = nil
poll_callback = -1
MODE_IDLE = 0
MODE_SEND = 1
MODE_RECV = 2

--- Make sure these line up with the .link_debug addresses in PTGB.
LINK_DEBUG      = 0x0203FFFC

LD_REG_SIOCNT   = LINK_DEBUG
LD_REG_SIODATA8 = LINK_DEBUG + 2

function logf(fmt, ...)
    local tag = "[UNK]"
    if emu and emu:platform() == C.PLATFORM.GBA then
        tag = "[GBA]"
    elseif emu and emu:platform() == C.PLATFORM.GB then
        tag = "[GBC]"
    end

    local str = string.format("%s " .. fmt, tag, ...)
    console:log(str)
end

function EnableOutput(filename)
    if output_file then
        output_file:close()
    end
    output_file, err = io.open(filename, "wb")
    if not output_file then
        console:error("Could not open " .. filename .. " for writing: " .. err)
    end
end

function SendByte(byte)
    logf("SEND [0x%04x] 0x%02x", emu:currentFrame(), byte)

    local bytes = string.char(byte)
    if output_file then
        output_file:write(bytes)
        output_file:flush()
    end
    if sock then
        sock:send(bytes)
    end
end


function DisableWatchpoint()
    if watchpoint ~= -1 then
        emu:clearBreakpoint(watchpoint)
        watchpoint = -1
    end
end

function SocketError()
    if sock then
        console:error("Socket error")
        DisableWatchpoint()

        sock:close()
        sock = nil
    else
        console:error("Unknown socket error")
    end
end

function PollSocket()
    if sock then
        local status, err = sock:hasdata()
        if err then
            console:error("Socket error " .. err)
            SocketError()
        end

        -- SIOCNT START writes can happen while the watchpoint is temporarily
        -- disabled during reply handling. Polling here lets us recover
        -- transfers that the watchpoint missed.
        if emu and emu:platform() == C.PLATFORM.GBA then
            GBA_Watchpoint()
        end
    end
end

function Stop()
    logf("Stopping...")
    DisableWatchpoint()
    if poll_callback ~= -1 then
        callbacks:remove(poll_callback)
        poll_callback = -1
    end

    if sock then
        sock:close()
        sock = nil
    end
    if output_file then
        output_file:close()
        output_file = nil
    end
    if server then
        server:close()
        server = nil
    end
    
end


frame_callback = -1
gba_transfer_pending = false
gba_last_start_state = false

function SerialExchangeByte(input)
    if not sock then return false end
    -- Check if ready --
    local rSC = read_io(REG_SIOCNT)
    if (rSC & SIO_START) == 0 then
         

            if defer_watchpoint == -1 then
                -- Defer the result until the game is ready. --
                defer_watchpoint = emu:setWatchpoint(
                    function()
                        SerialExchangeByte(input)
                    end,
                    REG_SIOCNT,
                    C.WATCHPOINT_TYPE.WRITE
                )
            end
            if frame_callback == -1 then
                frame_callback = callbacks:add("frame", function() SerialExchangeByte(input) end)
            else
                -- SendByte(0xFF) -- fail
                --callbacks:remove(frame_callback)
                --frame_callback = -1
            end
            return false -- not ready --
    end
    -- Disable the watchpoint --
    DisableWatchpoint()

    if defer_watchpoint ~= -1 then
        emu:clearBreakpoint(defer_watchpoint)
        defer_watchpoint = -1
    end
    if frame_callback ~= -1 then 
        callbacks:remove(frame_callback)
        frame_callback = -1
    end

    local output = read_io(REG_SIODATA8)

    -- Log --
    logf("RECV [0x%04x] 0x%02x", emu:currentFrame(), input)

    -- Write the new byte --
    write_io(REG_SIODATA8, input & 0xFF)
    
    -- Clear the start and ready flags. --
    rSC = (rSC & ~SIO_START)
    write_io(REG_SIOCNT, rSC)

    if emu:platform() == C.PLATFORM.GBA then
        -- Treat the next SIOCNT START write as a new transaction.
        gba_transfer_pending = false
        gba_last_start_state = false
    end

    -- GB specific code --
    if emu:platform() == C.PLATFORM.GB then
        -- GBA sends first. --
        SendByte(output)
    
        -- Trigger an interrupt --
        local rIF = read_io(REG_IF)
        rIF = rIF | IF_SERIAL
        write_io(REG_IF, rIF)
    end
    MODE = MODE_IDLE
    EnableWatchpoint()
    return true
end

function HandleReceive()
    if not sock then return end

    -- Receive the byte from the GB socket --
    local p, err = sock:receive(1)
    if p then
        local input = string.byte(p)

        -- DisableWatchpoint()

        -- if emu:platform() == C.PLATFORM.GBA then
        --     -- The GBA needs a second flag set to enable transfer --
        --     local rSC = read_io(REG_SIOCNT)
        --     rSC = rSC | SIO_READY
        --     write_io(REG_SIOCNT, rSC)
        -- end

        -- Write the byte from the GB to link_debug.input_byte and write true to has_input --
        SerialExchangeByte(input)
    else
        if err ~= socket.ERRORS.AGAIN then
            SocketError()
        end
    end
end

--- Host (GBA) code ---

function GBA_Watchpoint()
    -- if mode == MODE_RECV then return end

    local rSC = read_io(REG_SIOCNT)
    local start_set = (rSC & SIO_START) ~= 0

    -- DisableWatchpoint()
    -- rSC = rSC | SIO_READY
    -- write_io(REG_SIOCNT, rSC)
    -- EnableWatchpoint()

    if not start_set then
        gba_last_start_state = false
        return
    end

    if not sock then return end
    if gba_transfer_pending or gba_last_start_state then return end
    gba_last_start_state = true
    gba_transfer_pending = true

    -- Send it to the GB --
    is_sending = true

    SendByte(read_io(REG_SIODATA8) & 0xFF)
    
end

function GBA_Accept() -- ST_Accept
    if poll_callback ~= -1 then
        callbacks:remove(poll_callback)
        poll_callback = -1
    end 
    if sock then
        -- Reconnection --
        DisableWatchpoint()
        sock:close()
        sock = nil
    end
    gba_transfer_pending = false
    gba_last_start_state = false


    -- Accept the connection --
    while true do
        local tmp_sock
        tmp_sock, err = server:accept()
        if err then
            if err ~= socket.ERRORS.AGAIN then
                console:error("Accept " .. err)
                Stop()
                return
            end
        else
            -- Setup callbacks --
            sock = tmp_sock
            tmp_sock:add("received", HandleReceive)
            tmp_sock:add("error", SocketError)
            logf("Connected")

            break
        end
    end

    poll_callback = callbacks:add("frame", PollSocket)
    -- Enable the watchpoint to start monitoring for link debug events. --
    -- local rSC = read_io(REG_SIOCNT)
    -- rSC = rSC | SIO_READY
    -- write_io(REG_SIOCNT, rSC)

    EnableWatchpoint()
end

function GBA_Setup()
    if server ~= nil then
        server:close()
        server = nil
    end

    server, err = socket.bind(nil, PORT)
    if err then
        console:error("Bind error " .. err)
        return false
    end

    local ok
    ok, err = server:listen()
    if err then
        console:error("Error listening: " .. err)
        server:close()
        return false
    else
        logf("PTGB Link Debug Script: Listening on port %d", PORT)
        server:add("received", GBA_Accept)
        return true
    end

end


--- GB client code ---

--[[
  The GB requires us to emulate the link cable enough to trick Pokémon.
  Thankfully, mGBA is not picky on the GB I/O registers, so this is a simple task.
]]--

--- Since mGBA is much more lenient on the GB link cable registers, we can modify memory directly. --


function GB_Error()
    console:error("Socket error, disconnecting...")
    if sock then
        sock:close()
        sock = nil
    end
    GB_TryConnect()
end

function GB_TryConnect()
    local tmp_sock = socket.tcp()

    if tmp_sock and tmp_sock:connect("127.0.0.1", PORT) then
        logf("PTGB Link Debug Script: Connected via port %d", PORT)

        if poll_callback ~= -1 then
            callbacks:remove(poll_callback)
            poll_callback = -1
        end
        poll_callback = callbacks:add("frame", PollSocket)

        sock = tmp_sock
        tmp_sock:add("received", HandleReceive)
        tmp_sock:add("error", GB_Error)

        return true
    else
        tmp_sock:close()
        if poll_callback == -1 then
            -- Poll each frame. Only print once --
            logf("Waiting for connection...")
            poll_callback = callbacks:add("frame", GB_TryConnect)
        end
        return false
    end
end

-- mGBA doesn't let you get the No-Intro title from Lua, sadly. --
ROM_INFO = {
    -- CRC32         Game         Language          Rev.   No-Intro title -- 

    -- Red --
    [0x13652705] = { "Red",      "Japanese",        0,    "Pocket Monsters - Aka (Japan) (SGB Enhanced)" },
    [0xb77be1e0] = { "Red",      "Japanese",        1,    "Pocket Monsters - Aka (Japan) (Rev 1) (SGB Enhanced)" },
    [0x9f7fdd53] = { "Red",      "English",         0,    "Pokemon - Red Version (USA, Europe) (SGB Enhanced)" },
    [0xd8507d8a] = { "Red",      "Spanish",         0,    "Pokemon - Edicion Roja (Spain) (SGB Enhanced)" },
    [0x89197825] = { "Red",      "German",          0,    "Pokemon - Rote Edition (Germany) (SGB Enhanced)" },
    [0x337fce11] = { "Red",      "French",          0,    "Pokemon - Version Rouge (France) (SGB Enhanced)" },
    [0x2945aceb] = { "Red",      "Italian",         0,    "Pokemon - Versione Rossa (Italy) (SGB Enhanced)" },

    -- Green --
    [0xbaeacd2b] = { "Green",    "Japanese",        0,    "Pocket Monsters - Midori (Japan) (SGB Enhanced)" },
    [0x37ae8dc4] = { "Green",    "Japanese",        1,    "Pocket Monsters - Midori (Japan) (Rev 1) (SGB Enhanced)" },

    -- Blue --
    [0xe4468d14] = { "Blue",     "Japanese",        0,    "Pocket Monsters - Ao (Japan) (SGB Enhanced)" },
    [0xd6da8a1a] = { "Blue",     "English",         0,    "Pokemon - Blue Version (USA, Europe) (SGB Enhanced)" },
    [0xd95416f9] = { "Blue",     "Spanish",         0,    "Pokemon - Edicion Azul (Spain) (SGB Enhanced)" },
    [0x9c336307] = { "Blue",     "German",          0,    "Pokemon - Blaue Edition (Germany) (SGB Enhanced)" },
    [0x50e2fc1d] = { "Blue",     "French",          0,    "Pokemon - Version Bleue (France) (SGB Enhanced)" },
    [0x4d0984a9] = { "Blue",     "Italian",         0,    "Pokemon - Versione Blu (Italy) (SGB Enhanced)" },

    -- Yellow --
    [0x4ec85504] = { "Yellow",   "Japanese",        0,    "Pocket Monsters - Pikachu (Japan) (SGB Enhanced)" },
    [0xa2545d33] = { "Yellow",   "Japanese",        1,    "Pocket Monsters - Pikachu (Japan) (Rev 1) (SGB Enhanced)" },
    [0xfd3da7ff] = { "Yellow",   "Japanese",        2,    "Pocket Monsters - Pikachu (Japan) (Rev 2) (SGB Enhanced)" },
    [0xe9e6483a] = { "Yellow",   "Japanese",        3,    "Pocket Monsters - Pikachu (Japan) (Rev 3) (SGB Enhanced)" },
    [0x7d527d62] = { "Yellow",   "English",         0,    "Pokemon - Yellow Version - Special Pikachu Edition (USA, Europe) (CGB+SGB Enhanced)" },
    [0x964b7a10] = { "Yellow",   "Spanish",         0,    "Pokemon - Edicion Amarilla - Edicion Especial Pikachu (Spain) (CGB+SGB Enhanced)" },
    [0x7a01e45a] = { "Yellow",   "German",          0,    "Pokemon - Gelbe Edition - Special Pikachu Edition (Germany) (CGB+SGB Enhanced)" },
    [0xd03426e9] = { "Yellow",   "French",          0,    "Pokemon - Version Jaune - Edition Speciale Pikachu (France) (CGB+SGB Enhanced)" },
    [0x8b56fe33] = { "Yellow",   "Italian",         0,    "Pokemon - Versione Gialla - Speciale Edizione Pikachu (Italy) (CGB+SGB Enhanced)" },

    -- Gold --
    [0x524478d4] = { "Gold",     "Japanese",        0,    "Pocket Monsters Kin (Japan) (SGB Enhanced) (GB Compatible)" },
    [0x4ef7f2a5] = { "Gold",     "Japanese",        1,    "Pocket Monsters Kin (Japan) (Rev 1) (SGB Enhanced) (GB Compatible)" },
    [0x6bde3c3e] = { "Gold",     "English",         0,    "Pokemon - Gold Version (USA, Europe) (SGB Enhanced) (GB Compatible)" },
    [0x3434a92b] = { "Gold",     "Spanish",         0,    "Pokemon - Edicion Oro (Spain) (SGB Enhanced) (GB Compatible)" },
    [0x4889dfaa] = { "Gold",     "German",          0,    "Pokemon - Goldene Edition (Germany) (SGB Enhanced) (GB Compatible)" },
    [0x37a70702] = { "Gold",     "French",          0,    "Pokemon - Version Or (France) (SGB Enhanced) (GB Compatible)" },
    [0x4c184ce3] = { "Gold",     "Italian",         0,    "Pokemon - Versione Oro (Italy) (SGB Enhanced) (GB Compatible)" },
    [0x249a7a66] = { "Gold",     "Korean",          0,    "Pocket Monsters Geum (Korea)" },

    -- Silver --
    [0xbe1b928a] = { "Silver",   "Japanese",        0,    "Pocket Monsters Gin (Japan) (SGB Enhanced) (GB Compatible)" },
    [0x0aea5383] = { "Silver",   "Japanese",        1,    "Pocket Monsters Gin (Japan) (Rev 1) (SGB Enhanced) (GB Compatible)" },
    [0x8ad48636] = { "Silver",   "English",         0,    "Pokemon - Silver Version (USA, Europe) (SGB Enhanced) (GB Compatible)" },
    [0x1d9faac5] = { "Silver",   "Spanish",         0,    "Pokemon - Edicion Plata (Spain) (SGB Enhanced) (GB Compatible)" },
    [0x96c9db95] = { "Silver",   "German",          0,    "Pokemon - Silberne Edition (Germany) (SGB Enhanced) (GB Compatible)" },
    [0xe0c216ea] = { "Silver",   "French",          0,    "Pokemon - Version Argent (France) (SGB Enhanced) (GB Compatible)" },
    [0xcba6d2d4] = { "Silver",   "Italian",         0,    "Pokemon - Versione Argento (Italy) (SGB Enhanced) (GB Compatible)" },
    [0x9cc1f90f] = { "Silver",   "Korean",          0,    "Pocket Monsters Eun (Korea)" },

    -- Crystal --
    [0x270c4ecc] = { "Crystal",  "Japanese",        0,    "Pocket Monsters - Crystal Version (Japan)" },
    [0xee6f5188] = { "Crystal",  "English (US)",    0,    "Pokemon - Crystal Version (USA)" },
    [0x3358e30a] = { "Crystal",  "English (US/EU)", 1,    "Pokemon - Crystal Version (USA, Europe) (Rev 1)" },
    [0xbb6dd80c] = { "Crystal",  "English (AUS)",   0,    "Pokemon - Crystal Version (Australia)" },
    [0xff0a6f8a] = { "Crystal",  "Spanish",         0,    "Pokemon - Edicion Cristal (Spain)" },
    [0x616d85de] = { "Crystal",  "German",          0,    "Pokemon - Kristall-Edition (Germany)" },
    [0x878b2aa7] = { "Crystal",  "French",          0,    "Pokemon - Version Cristal (France)" },
    [0xd45ac039] = { "Crystal",  "Italian",         0,    "Pokemon - Versione Cristallo (Italy)" },
}

function GB_Setup()
    
    -- Try to identify the ROM --
    local crc32_raw = emu:checksum(C.CHECKSUM.CRC32)

    -- mGBA returns a binary string in big endian, convert it to a number --
    local crc32 = (string.byte(crc32_raw, 1) << 24) |
                  (string.byte(crc32_raw, 2) << 16) |
                  (string.byte(crc32_raw, 3) <<  8) |
                  (string.byte(crc32_raw, 4) <<  0)

    if ROM_INFO[crc32] then
        -- Print info --
        local game_type  = ROM_INFO[crc32][1]
        local game_lang  = ROM_INFO[crc32][2]
        local game_rev   = ROM_INFO[crc32][3]
        local game_title = ROM_INFO[crc32][4]

        logf("Detected an official Pokémon game!")
        logf(" - CRC32:    0x%08x", crc32)
        logf(" - ROM name: %s", game_title)
        logf(" - Game:     %s", game_type)
        logf(" - Language: %s", game_lang)
        logf(" - Revision: %d", game_rev)
    else
        logf("Warning: Unknown CRC32 0x%08x", crc32)
    end

    GB_TryConnect()
    return true
end

function Setup()
    if emu then
        logf("Setting up...")
        if emu:platform() == C.PLATFORM.GBA then

            REG_SIODATA8 = LD_REG_SIODATA8
            REG_SIOCNT = LD_REG_SIOCNT
            -- PTGB doesn't actually use serial interrupts, and we can't manually
            -- set the interrupts.
            REG_IF = 0

            SIO_START  = 0x0080
            SIO_READY  = 0x0000
            IF_SERIAL = 0x0080

            function write_io(addr, val)
                emu:write16(addr, val)
            end

            function read_io(addr)
                return emu:read16(addr)
            end

            function EnableWatchpoint()
                watchpoint = emu:setWatchpoint(GBA_Watchpoint, REG_SIOCNT, C.WATCHPOINT_TYPE.WRITE)
            end

            if not GBA_Setup() then
                console:error("Setup failed!")
            end
            
        else
            REG_SIODATA8 = 0xFF01
            REG_SIOCNT = 0xFF02
            REG_IF = 0xFF0F

            SIO_START  = 0x80
            SIO_READY = 0x00
            IF_SERIAL = 0x08
            function write_io(addr, val)
                emu:write8(addr, val)
            end

            function read_io(addr)
                return emu:read8(addr)
            end

            function EnableWatchpoint()
                -- watchpoint = emu:setWatchpoint(GB_Watchpoint, REG_SIOCNT, C.WATCHPOINT_TYPE.WRITE)
            end


            if not GB_Setup() then
                console:error("Setup failed!")
            end
        end
    end
end


callbacks:add("start", Setup)
callbacks:add("stop", Stop)

if emu then
    Setup()
end
