#!/usr/bin/env python
import sys
from docopt import docopt

usage = \
"""
Usage:
    tt_error.py <actual> <trial>
"""

def tt_order(path):
  f = open(path)
  return list(reversed([color for (weight,color) in [line.rstrip().split(" ") for line in f.readlines()]]))



def main():
  args = docopt(usage)
  actual = tt_order(args['<actual>'])
  trial = tt_order(args['<trial>'])
  pairs = zip(actual,trial)
  same = [x == y for (x,y) in pairs]
  try:
    index = same.index(False)
  except ValueError:
    print "All values match"
  else:
    print "First mismatch at index", index
  print same.count(True), "of", len(same), "items matched positions"
  print len(set(actual).intersection(set(trial))), " of ", len(set(actual).union(set(trial))), "colors matched"
  return 0

if __name__ == '__main__':
    sys.exit(main())
