FROM devkitpro/devkitarm

LABEL author="Poke Transporter GB"

USER root

ARG USER_ID
ARG GROUP_ID

ENV DEBIAN_FRONTEND="noninteractive"

RUN apt update && apt install -y build-essential
