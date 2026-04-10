FROM debian:12-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
       sudo \
       passwd \
       login \
       procps \
       make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/reto3
COPY include ./include
COPY src ./src
COPY Makefile ./Makefile

RUN chmod +x src/main.sh src/user/user.sh src/utils/validation.sh src/policy/policy.sh

CMD ["/bin/bash"]
