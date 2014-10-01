//
//  MIKMIDISequence.h
//  MIDI Files Testbed
//
//  Created by Andrew Madsen on 5/21/14.
//  Copyright (c) 2014 Mixed In Key. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>


@class MIKMIDITrack;
@class MIKMIDIDestinationEndpoint;

@interface MIKMIDISequence : NSObject

@property (nonatomic, readonly) MIKMIDITrack *tempoTrack;
@property (nonatomic, readonly) NSArray *tracks;

@property (nonatomic, readonly) MusicSequence musicSequence;

@property (nonatomic) MusicTimeStamp length;    // Set to MIKMIDISequenceLongestTrackLength to use the length of the longest track
@property (nonatomic, readonly) Float64 durationInSeconds;

@property (nonatomic, readonly) NSData *dataValue;

@property (copy, nonatomic) void (^callBackBlock)(MIKMIDITrack *track, MusicTimeStamp eventTime, const MusicEventUserData *eventData, MusicTimeStamp startSliceBeat, MusicTimeStamp endSliceBeat);

@property (nonatomic, strong, readwrite) MIKMIDIDestinationEndpoint *destinationEndpoint;

+ (instancetype)sequence;

+ (instancetype)sequenceWithFileAtURL:(NSURL *)fileURL error:(NSError **)error;
- (instancetype)initWithFileAtURL:(NSURL *)fileURL error:(NSError **)error;

+ (instancetype)sequenceWithData:(NSData *)data;
- (instancetype)initWithData:(NSData *)data;

- (BOOL)writeToURL:(NSURL *)fileURL error:(NSError **)error;

- (MIKMIDITrack *)addTrack;
- (BOOL)removeTrack:(MIKMIDITrack *)track;

- (MusicTimeStamp)equivalentTimeStampForLoopedTimeStamp:(MusicTimeStamp)loopedTimeStamp;

// Convenience methods for working with the tempo track
- (NSArray *)timeSignatureEvents;
- (NSArray *)tempoEvents;

- (BOOL)setOverallTempo:(Float64)bpm;
- (BOOL)setTempo:(Float64)bpm atTimeStamp:(MusicTimeStamp)timeStamp;
- (BOOL)getTempo:(Float64 *)bpm atTimeStamp:(MusicTimeStamp)timeStamp;

@end


FOUNDATION_EXPORT const MusicTimeStamp MIKMIDISequenceLongestTrackLength;