#!/bin/bash
find . -iname "*.tex" -exec bash -c 'echo {}; cat licensehead {} > {}.neu; mv {}.neu {}' \;
