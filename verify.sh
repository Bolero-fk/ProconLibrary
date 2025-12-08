#!/usr/bin/env bash
set -eu

# このリポジトリ専用の秘密設定があれば読み込む
if [ -f "./.env.local" ]; then
  . "./.env.local"
fi

competitive-verifier oj-resolve --config ./.verify-helper/config.toml --include "$@" \
  | competitive-verifier verify --verify-json /dev/stdin
