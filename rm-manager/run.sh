#!/bin/bash
cd "$(dirname "$0")"
rtems-run --rtems-bsps=erc32-sis build/sparc-rtems5-erc32/rm-manager.exe
