#!/bin/sh

docker run -ti --rm -v $(pwd):/work -w="/work" eguerin/antlr4cpp
