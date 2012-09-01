#!/usr/bin/python2
# Download jamendo albums.

# Import necessary libs
from os import system
import urllib
import argparse
import json
import re
import sys

# Set up argument parsing
parser = argparse.ArgumentParser(description='Search jamendo for albums.')
parser.add_argument("-a", dest="artist", type=str, required=True, help="Search for an artist by name. Required.")

# Parse all arguments ----------------------------------------------------------------------------------#
args = parser.parse_args();

# a simple jamendo api urlmap --------------------------------------------------------------------------#

urlmap = {
    "artist":    lambda (s): "http://api.jamendo.com/get2/id+name/artist/json/?name="+str(s),
    "list":      lambda (s): "http://api.jamendo.com/get2/name+id/album/json/?artist_name="+str(s),
    "album":     lambda (s): "http://www.jamendo.com/get/album/id/album/archiverestricted/redirect/"+str(s)+"/?are=ogg3"
    }
#-------------------------------------------------------------------------------------------------------#

def getAlbumList(artist_name):

  # Get results from Jamendo in JSON format
  query = urlmap["list"](artist_name)
  f = urllib.urlopen(query)
  results = json.loads(f.read())

  # create and return a list of hashes containing the albumname and the album id
  return [ {"name": items['name'], "id": items['id'] } for items in results]

#-------------------------------------------------------------------------------------------------------#

def getArtistList(artist):

  # Get results from Jamendo in JSON format
  query = urlmap["artist"](artist)

  f = urllib.urlopen(query)
  results = json.loads(f.read())


  # create and return a list of hashes containing the albumname and the album id
  return [ {"name": items['name'], "id": items['id'] } for items in results]

#-------------------------------------------------------------------------------------------------------#

pick = 0


def printList(list):
  for i in range(len(list)):
    print "%d: %s" % ( i, list[i]["name"])
    pick = input("enter number to fetch: ")
  return pick

def startup():
  artists = getArtistList(args.artist)
  printList(artists)
  albums = getAlbumList(artists[int(pick)]["name"])
  for i in range(len(albums)):
    print "%d: %s" % ( i, albums[i]["name"])

  dl = input("enter number to fetch: ")
  dlink = urlmap['album'](albums[dl]["id"])
  name = re.escape(artists[int(pick)]["name"]+"-"+albums[dl]["name"])

  global dlink

  def dlProgress(count, blockSize, totalSize):
    percent = int(count*blockSize*100/totalSize)
    sys.stdout.write("\r" + dlink + "...%d%%" % percent)
    sys.stdout.flush()
    return

  urllib.urlretrieve(dlink, name+".zip", reporthook=dlProgress)

  return

startup()
