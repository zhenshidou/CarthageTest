//
//  QuickTrackingSDK.h
//  QuickTrackingSDK
//
//  Created by 钰昭 on 2024/12/31.
//
#import <Foundation/Foundation.h>

#if TARGET_OS_IOS || TARGET_OS_TV
#import <UIKit/UIKit.h>
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#endif

#import <QuickTrackingSDK/QuickTrackingSDK+Public.h>
#import <QuickTrackingSDK/QTSDKConfig.h>
