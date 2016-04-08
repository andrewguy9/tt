#!/usr/bin/env python
import sys
from docopt import docopt
from tempfile import NamedTemporaryFile
import subprocess

usage = \
"""
Usage:
    tt_merge.py <size> <sample> <sample>...
"""

def tt_parse(path):
  f = open(path)
  return [(color,weight) for (weight,color) in [line.rstrip().split(" ") for line in f.readlines()]]

def main():
  args = docopt(usage)
  samples = [ iter(tt_parse(sample_path)) for sample_path in args['<sample>']]
  with NamedTemporaryFile() as fd:
    while(len(samples) > 0):
      remaining = []
      for sample in samples:
        try:
          color,weight = sample.next()
        except StopIteration:
          pass
        else:
          print >>fd, weight,color
          remaining.append(sample)
      samples = remaining
    fd.flush()
    with open(fd.name, 'r') as reader:
      subprocess.call(["./tt_perf.out", args['<size>']], stdin=reader)
  return 0

if __name__ == '__main__':
    sys.exit(main())
