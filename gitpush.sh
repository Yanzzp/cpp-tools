#!/bin/bash

# 检查是否提供了命令行参数
if [ -z "$1" ]; then
    echo "No commit message provided, using default message 'update'."
    COMMIT_MESSAGE="update"
else
    COMMIT_MESSAGE="$1"
fi

# 执行 Git 命令
git add .
git commit -m "$COMMIT_MESSAGE"
git push
