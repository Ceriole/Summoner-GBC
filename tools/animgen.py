import argparse
import json
import os

def main():
    args = parseArgs()
    data = parseJson(json.load(args.inputfile))
    outfilepath = os.path.splitext(args.output)[0]
    targext = os.path.splitext(args.output)[1].lower()
    sourcetype = targext
    if args.force_type != None:
        sourcetype = args.force_type
    typeslist = ['c', 'h']
    typeslist.remove(sourcetype)
    othertype = typeslist[0]
    descriptor = os.path.basename(outfilepath)
    if args.name != None:
        descriptor = args.name
    bank = None
    if args.bank != None:
        if args.bank in range(0,256):
            bank = args.bank
        else:
            raise ValueError('Bank must be within 0 and 255! Bank: ' + str(args.bank))
    if args.verbose:
        print(args.inputfile.name, 'to C data:', descriptor, end='')
        if bank != None:
            print('(Bank: ' + str(args.bank) + ')')
        print('Generating', sourcetype, 'file to', args.output)
        if args.module:
            print('Generating', othertype, 'file to', outfilepath + '.' + othertype)
    data['meta']['bank'] = bank
    data['meta']['descriptor'] = descriptor
    data['meta']['type'] = sourcetype


    if args.module:
        data['meta']['type'] = othertype

def parseArgs():
    parser = argparse.ArgumentParser(
        description='Converts Aseprite JSON files into C headers and gameboy-compatible byte data.',
        epilog='Written by Ceriole in 2022 for SUMMONER.'
    )
    parser.add_argument('inputfile', type=open, help='Input Aseprite generated JSON')
    parser.add_argument('-o', '--output', type=str, help='Output .c or .h file.', required=True)
    parser.add_argument('-f', '--fps', type=float, default=59.77, help='Used to convert millisecond delays to frame delays. (GB runs at ~59.77 fps)')
    parser.add_argument('-n', '--name', type=str, help='Name of the C descriptor to generate.')
    parser.add_argument('--force-type', type=str, choices=['c', 'h'], default='c', help='Force the type of C source file to generate.')
    parser.add_argument('-v', '--verbose', action='store_true', help='Print extra information.')
    parser.add_argument('-m', '--module', action='store_true', help='Create both .c and .h files.')
    parser.add_argument('-b', '--bank', type=int, help='Set the source file\'s bank for GBDK. [0..255]')
    return parser.parse_args()

def parseJson(json_data: dict) -> dict[str, dict]:
    data = {}
    data['meta'] = json_data['meta']
    frames = []
    for frame_data in json_data['frames']:
        frames.append(parseFrame(frame_data))
    return data

def parseFrame(frame_data: dict) -> dict[str, int]:
    frame = {}
    
    return frame

if __name__ == '__main__':
    main()