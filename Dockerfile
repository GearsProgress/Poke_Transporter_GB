FROM devkitpro/devkitarm:20251117

LABEL author="Poke Transporter GB"

USER root

ARG USER_ID
ARG GROUP_ID

ENV DEBIAN_FRONTEND="noninteractive"

RUN apt update && apt install -y build-essential cmake bison flex pkg-config libpng-dev git python3-pip python3-png python3-debugpy && pip install pandas requests openpyxl --break-system-packages

RUN git clone https://github.com/gbdev/rgbds.git && cd rgbds && make -j$(nproc) && make install
