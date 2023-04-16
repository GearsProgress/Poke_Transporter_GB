//Created by Laqieer https://github.com/laqieer/libsavgba

#ifndef ERR_DEF_H
#define ERR_DEF_H

enum ErrorCode {
    E_SUCCESS = 0, ///< No error.
    E_INVALID_PARAM, ///< Invalid input parameter.
    E_OUT_OF_RANGE, ///< Address is out of range.
    E_VERIFY_FAIL, ///< Failed to verify written data.
    E_UNSUPPORTED_DEVICE, ///< Device type is not supported.
    E_TIMEOUT, ///< Operation timeout.
};

/**
 * @brief Error codes.
 *
 * Use `SavErrCodes[ErrorCode]` to get error code names.
 */
extern const char * const SavErrCodes[];

/**
 * @brief Error messages.
 *
 * Use `SavErrMsgs[ErrorCode]` to get error code messages.
 */
extern const char * const SavErrMsgs[];

#endif /* ERR_DEF_H */
