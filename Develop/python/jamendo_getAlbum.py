#!/usr/bin/python2
# Special thanks to scf for his assistance
# Download jamendo albums --------------------------------------------------------------------------------------------------#


# Import necessary libs ----------------------------------------------------------------------------------------------------#
import urllib
import argparse
import json
import sys


# Set up argument parsing --------------------------------------------------------------------------------------------------#
parser = argparse.ArgumentParser(description='Search jamendo for albums.')
parser.add_argument("-a", dest="artist", type=str, required=False, help="Search for an artist by name. Required.")


# Parse all arguments ------------------------------------------------------------------------------------------------------#
args = parser.parse_args();


# a simple jamendo api urlmap ----------------------------------------------------------------------------------------------#
urlmap = {
    "list":      lambda (s): "http://api.jamendo.com/get2/name+id/album/json/?artist_name="+str(s),
    "album":     lambda (s): "http://www.jamendo.com/get/album/id/album/archiverestricted/redirect/"+str(s)+"/?are=ogg3"
    }


# Get list of albums using artist name -------------------------------------------------------------------------------------#
def getAlbumList(artist_name):

  query = urlmap["list"](artist_name)
  f = urllib.urlopen(query)
  results = json.loads(f.read())

  return [ items for items in results ]


# Startup function  --------------------------------------------------------------------------------------------------------#
def startup():

  def makeProgress(name):

    def dlProgress(count, blockSize, totalSize):
      percent = int(count*blockSize*100/totalSize)
      sys.stdout.write("\r" + name + "...%d%%" % percent)
      sys.stdout.flush()

    return dlProgress

  albums = getAlbumList(args.artist)
  for i in range(len(albums)):
    dlink = urlmap['album'](albums[i]["id"])
    name = args.artist+"-"+albums[i]["name"]
    urllib.urlretrieve(dlink, name+".zip", reporthook=makeProgress(dlink))

startup()
