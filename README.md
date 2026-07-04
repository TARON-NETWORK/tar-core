# tar-core — TAR wallet & node

Node (tard) and wallet (tar-wallet-cli, tar-wallet-rpc) for the TAR network.
Proof-of-work: RandomTAR.

## Create a TAR wallet

Build (below), then run:

    ./tar-wallet-cli

Choose "create new wallet", set a name and password. It gives you your address
(it starts with X) and a recovery seed. Save the seed. Use that address to
receive TAR and to mine (with xmrig-tar).

## Build (Linux)

    git clone https://github.com/TARON-NETWORK/tar-core.git
    cd tar-core
    make -j$(nproc)

Binaries appear in build/Linux/main/release/bin: tard, tar-wallet-cli, tar-wallet-rpc.
Released under GPLv3 (see LICENSE).
