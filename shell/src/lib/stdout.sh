#!/bin/bash

success() {
  echo -e "\033[32m\033[1m[$(date "+%H:%M:%S")] $1\033[0m"
}

error() {
  echo -e "\033[31m\033[1m[$(date "+%H:%M:%S")] $1\033[0m"
}
