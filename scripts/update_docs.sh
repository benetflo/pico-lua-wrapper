#!/bin/bash

cd ..
rm -rf docs/
ldoc .
mv doc/ docs/
mv docs/docs.html docs/index.html

