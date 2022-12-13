import argparse
import json

def main():
    args = parseArgs()
    data = parseJson(json.load(args.inputfile))

def parseArgs():
    parser = argparse.ArgumentParser(
        description='Converts Aseprite JSON files into C headers and gameboy-compatible byte data.',
        epilog='Written by Ceriole in 2022 for SUMMONER.'
    )
    parser.add_argument('inputfile', type=open, help='Input Aseprite generated JSON')
    parser.add_argument('-o', '--output', type=argparse.FileType('w'), help='Output .c file. Will automatically generate .h file in the same location. Default is the same location and name as the input file.', nargs='?')
    parser.add_argument('-8', '--8x8', action='store_true', help='Treat the data as if it were being made from 8x8 tiles')
    parser.add_argument('-f', '--fps', type=float, default=59.77, help='Used to convert millisecond delays to frame delays. (GB runs at ~59.77 fps)')
    return parser.parse_args()

def parseJson(json_data: dict):
    data = {}
    data['meta'] = json_data['meta']
    frames = []
    for frame_data in json_data['frames']:
        frames.append(parseFrame(frame_data))

def parseFrame(frame_data: dict):
    frame = {}

if __name__ == '__main__':
    main()