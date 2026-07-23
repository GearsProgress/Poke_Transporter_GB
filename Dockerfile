FROM devkitpro/devkitarm:20260610

LABEL author="Striaton Lab Team"
LABEL name="Poke Transporter GB"

USER root

ARG USER_ID
ARG GROUP_ID

ENV DEBIAN_FRONTEND="noninteractive"
ENV IS_PTGB=true

RUN apt-get update && apt-get install -y build-essential cmake bison flex pkg-config libpng-dev git python3-pip jq && pip install --root-user-action=ignore pandas requests openpyxl debugpy pypng --break-system-packages

RUN mkdir -p rgbds && curl -fsSL https://github.com/gbdev/rgbds/releases/download/v1.0.2+hotfix/rgbds-linux-x86_64.tar.xz | tar -xJ -C rgbds && cd rgbds && ./install.sh

RUN git config --global --add safe.directory /ptgb