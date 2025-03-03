//
//  QuickTrackingSDK+Public.h
//  QuickTrackingSDK
//
//  Created by 钰昭 on 2024/12/31.
//

#ifndef QuickTrackingSDK_Public_h
#define QuickTrackingSDK_Public_h

typedef void (^QTShareResultHandler)(id __nullable result, NSError *__nullable error);

@class QTSDKConfig;

@interface QuickTrackingSDK : NSObject

/**
 * 通过配置参数，配置QuickTracking SDK
 *  此方法调用必须符合以下条件：
 *   1、必须在应用启动时调用，即在application:didFinishLaunchingWithOptions:中调用
 *   2、必须在主线程中调用
 *   3、必须在sdk其他方法调用之前调用
 * 如果不符合上述条件，存在丢失$$_app_start 应用启动事件风险
 */
+(void)launchWithConfig:(nonnull QTSDKConfig*)sdkConfig NS_SWIFT_NAME(launch(sdkConfig:));

/**
 * @abstract
 * 返回之前所初始化好的单例
 *
 * @discussion
 * 调用这个方法之前，必须先调用 launchWithConfig: 这个方法
 *
 * @return 返回的单例
 */
+(QuickTrackingSDK *_Nullable)sharedInstance;

/// 禁用SDK。调用后，SDK将不采集事件，不发送网络请求
+(void)disableSDK;

/// 开启SDK。如果之前SDK是禁止状态，调用后将恢复数据采集功能
+(void)enableSDK;

///  自定义设备Id
-(void)setCustomDeviceId:(NSString *_Nonnull)customDeviceID;

#pragma mark - 埋点相关
/**
 * @abstract
 * 自定义事件，用于追踪一个无自定义事件属性的 event
 * 使用前，请先到QuickTracking管理后台的数据采集-->埋点管理-->事件管理模块，创建相应的事件，然后在工程中传入相应的事件编码
 *
 * @param eventCode QuickTracking平台创建事件的事件编码
 */
- (void)event:( NSString *_Nonnull)eventCode;
/**
 *  @abstract
 *  自定义事件，用于追踪一个埋点行为
 *  使用前，请先到QuickTracking管理后台的数据采集-->埋点管理-->事件管理模块，创建相应的事件，然后在工程中传入相应的事件编码
 *
 *  @discussion
 *  properties 是一个Map
 *  其中的 key 是 属性的名称，必须是NSString
 *  其中的 value 是属性的值，只支持 NSString, NSNumber, NSArray 这些类型
 *  特别的，NSArray 类型的 value 中目前仅支持其中的元素是 NSString
 *
 *  @param eventCode QuickTracking平台创建事件的事件编码
 *  @param properties 事件自定义属性
 */
- (void)event:(NSString *_Nonnull)eventCode properties:(NSDictionary *_Nullable)properties;
/**
 *  @abstract
 *  自定义事件，用于追踪一个埋点行为
 *  使用前，请先到QuickTracking管理后台的数据采集-->埋点管理-->事件管理模块，创建相应的事件，然后在工程中传入相应的事件编码
 *
 *  @param eventCode QuickTracking平台创建事件的事件编码
 *  @param pageName 事件归属页面的页面编码
 */
- (void)event:(NSString *_Nonnull)eventCode pageName:(NSString *_Nonnull)pageName;
/**
 *  @abstract
 *  自定义事件，用于追踪一个埋点行为
 *  使用前，请先到QuickTracking管理后台的数据采集-->埋点管理-->事件管理模块，创建相应的事件，然后在工程中传入相应的事件编码
 *
 *  @discussion
 *  properties 是一个Map
 *  其中的 key 是 属性的名称，必须是NSString
 *  其中的 value 是属性的值，只支持 NSString, NSNumber, NSArray 这些类型
 *  特别的，NSArray 类型的 value 中目前仅支持其中的元素是 NSString
 *
 *  @param eventCode QuickTracking平台创建事件的事件编码
 *  @param pageName 事件归属页面的页面编码
 *  @param properties 事件自定义属性
 */
- (void)event:(NSString *_Nonnull)eventCode pageName:(NSString *_Nonnull)pageName property:(NSDictionary *_Nullable)properties;

/// flutter 全埋点点击事件协议透传原生iOS通道
/// @param eventCode QuickTracking平台创建事件的事件编码
/// @param mAutoTrackProperties flutter全埋点属性
/// @param mCustomProperties flutter全埋点事件自定义属性
//- (void)event:(NSString* _Nonnull)eventCode autoTrackProperties:(NSDictionary * _Nullable)mAutoTrackProperties customProperties:(NSDictionary* _Nullable)mCustomProperties;


-(void)onPageStart:(NSString *_Nonnull)pageName;

-(void)setPageProperties:(NSDictionary *_Nonnull)properties;

-(void)updateNextPageProperties:(NSDictionary *_Nonnull)properties;

-(void)onPageEnd:(NSString*_Nonnull)pageName;

#pragma mark - 属性相关
/**
 * 设置全局属性
 * @param properties 全局属性
 */
-(void)registerGlobalProperties:(NSDictionary * _Nonnull)properties;
/**
 * 删除全局属性中某个键值对
 * @param propertyName 希望删除的全局属性键值对的key
 */
-(void)unregisterGlobalProperty:(NSString *_Nonnull)propertyName;
/**
 * 获取全局属性中某个键值对的value
 * @param propertyName 希望获取全局属性键值对value的key
 * @return String | Number | Boolean | String[] | nil
 */
-(id _Nullable)getGlobalProperty:(NSString *_Nonnull)propertyName;
/**
 * 获取全部全局属性
 * @return NSDictionary | nil
 */
-(NSDictionary *_Nullable)getGlobalProperties;
/**
 * 清空全局属性
 */
-(void)clearGlobalProperties;

#pragma mark - 用户数据相关

/** 设置用户账号 **/
/// 使用onProfileSignIn方法后，如果结束该userId的统计，需要调用onProfieSignOff方法
/// @param userId 用户账号
- (void)onProfileSignIn:(NSString *_Nonnull)userId;

/** 移除用户账号 **/
/// 停止基于onProfileSignIn方法传入的用户账号Id的统计
- (void)onProfieSignOff;

/** 设置用户属性 **/
/// 设置用户属性方法，需注意！！！设置用户用户属性需先设置用户账号 onProfileSignIn
/// @param properties 用户属性
- (void)uploadUserProfile:(NSDictionary *_Nullable)properties;

#pragma mark - 应用唤起相关
/**
 * 判断是否符合为要求的 openURL
 *
 * @param url 唤起应用的 url
 * @return YES/NO
 */
- (BOOL)canHandleUrl:(NSURL *_Nonnull)url API_UNAVAILABLE(macos, tvos) NS_EXTENSION_UNAVAILABLE("HandleURL not supported for iOS extensions.");
/**
 * 处理 url scheme 跳转打开APP
 * @param url 打开本 app 的回调的 url
 */
- (BOOL)handleSchemeUrl:(NSURL *_Nonnull)url API_UNAVAILABLE(macos, tvos) NS_EXTENSION_UNAVAILABLE("HandleURL not supported for iOS extensions.");

#pragma mark - 分享裂变相关
/*
 * 分享参数化 获取API
 * @param url, 分享页面的url，必须传入
 * @param params 可能的分享参数，可以为null
 * {
 *   @"title": 分享标题, //可为null,最大长度 4*1024
 *   @"shareId": 来源分享Id, //可为 null
 *   @"campaign": 分享活动, //可为 null,最大长度 4*1024
 *   ... 待扩展
 * }
 * @param timeout 请求超时时间，单位秒，有效值范围：0~10（包含0和10），如果传入0，则使用sdk内部默认值3秒
 * @param shareResultHandler 结果回调对象，必须传入，不能为null
 */
-(void)requestShareParams:(NSString *_Nonnull)url
                   params:(NSDictionary *_Nonnull)params
                  timeout:(int)timeout
       shareResultHandler:(QTShareResultHandler _Nonnull)shareResultHandler
API_UNAVAILABLE(macos, tvos) NS_EXTENSION_UNAVAILABLE("HandleURL not supported for iOS extensions.");

/*
 * 来源分享参数获取 API
 * return @{ @"$$_ref_share_id": @"xxxxx", @"$$_ref_share_url": @"xxxxx"}
 **/
-(NSDictionary *_Nonnull)getRefShareParams
API_UNAVAILABLE(macos, tvos) NS_EXTENSION_UNAVAILABLE("HandleURL not supported for iOS extensions.");

#pragma mark - deprecated
/// 页面进入埋点，开始记录某个页面展示时长（该方法待废弃，仅做历史版本使用）
/// 使用方法：必须配对调用beginLogPageView:和endLogPageView:两个函数来完成页面统计，若只调用某一个函数不会生成有效数据。
/// 在该页面展示时调用beginLogPageView:，当退出该页面时调用endLogPageView:
/// @param pageName 页面事件编码
- (void)beginLogPageView:(NSString *_Nonnull)pageName __attribute__((deprecated("已过时， 请参考onPageStart")));

/// 页面离开埋点， 结束记录某个页面展示时长（该方法待废弃，仅做历史版本使用）
/// 使用方法：必须配对调用beginLogPageView:和endLogPageView:两个函数来完成页面统计，若只调用某一个函数不会生成有效数据。
/// 在该页面展示时调用beginLogPageView:，当退出该页面时调用endLogPageView:
/// @param pageName 页面事件编码
- (void)endLogPageView:(NSString *_Nonnull)pageName __attribute__((deprecated("已过时， 请参考onPageEnd")));

@end


#endif /* QuickTrackingSDK_Public_h */
