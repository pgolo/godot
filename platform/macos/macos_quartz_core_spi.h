/**************************************************************************/
/*  macos_quartz_core_spi.h                                               */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#pragma once

#import <Foundation/Foundation.h>
#import <Quartz/Quartz.h>

#include <stdint.h>

/*
 * WARNING: This header exposes private CoreAnimation SPI (CAContext).
 * Binaries built for the App Store must avoid emitting these Objective-C
 * symbols (they are non-public APIs). To exclude the private SPI, build
 * with -DGODOT_NO_PRIVATE_SPI (e.g. pass CCFLAGS and OBJCFLAGS via SCons).
 */

#ifndef GODOT_MACOS_QUARTZ_CORE_SPI_H
#define GODOT_MACOS_QUARTZ_CORE_SPI_H

#ifndef GODOT_NO_PRIVATE_SPI

// The CAContextID type identifies a CAContext across processes. This is the
// token that is passed from the process that is sharing the CALayer that it is
// rendering to the process that will be displaying that CALayer.
typedef uint32_t CAContextID;

// The CAContext has a static CAContextID which can be sent to another process.
// When a CALayerHost is created using that CAContextID in another process, the
// content displayed by that CALayerHost will be the content of the CALayer
// that is set as the |layer| property on the CAContext.
@interface CAContext : NSObject
+ (instancetype)contextWithCGSConnection:(CAContextID)contextId options:(NSDictionary *)optionsDict;
// Declare the contextId as readonly to avoid duplicate/contradictory declarations.
@property (readonly) CAContextID contextId;
@property(retain) CALayer *layer;
@end

// The CALayerHost is created in the process that will display the content
// being rendered by another process. Setting the |contextId| property on
// an object of this class will make this layer display the content of the
// CALayer that is set to the CAContext with that CAContextID in the layer
// sharing process.
@interface CALayerHost : CALayer
@property CAContextID contextId;
@end

// The CGSConnectionID is used to create the CAContext in the process that is
// going to share the CALayers that it is rendering to another process to
// display.
typedef uint32_t CGSConnectionID;
#ifdef __cplusplus
extern "C" {
#endif
extern CGSConnectionID CGSMainConnectionID(void);
#ifdef __cplusplus
}
#endif

// Private CoreAnimation NSString constant (private SPI).
FOUNDATION_EXPORT NSString *const kCAContextCIFilterBehavior;

#endif // !GODOT_NO_PRIVATE_SPI

#endif // GODOT_MACOS_QUARTZ_CORE_SPI_H