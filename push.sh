#!/bin/sh

SITE=https://github.com/ntopper/MD5AwSum

echo "commit -> '$1'"
git commit -a -m "$1"
echo "push..."
git push $SITE master

