//
//  QTSDKConfig.h
//  QuickTrackingSDK
//
//  Created by 钰昭 on 2024/12/31.
//

#import <Foundation/Foundation.h>
#import <QuickTrackingSDK/QTConstants.h>

NS_ASSUME_NONNULL_BEGIN
/**
 * @class
 * QuickTrackingSDK 初始化设置
 */
@interface QTSDKConfig : NSObject

/**
 * @description
 * 指定初始化方法，设置应用编码（appkey）收数域名（trackDomain）
 * @param appkey 应用编码
 * @param trackDomain 收数域名
 * @return 配置对象
 */
- (instancetype)initWithAppkey:(nonnull NSString*)appkey trackDomain:(nonnull NSString*)trackDomain launchOptions:(nullable id)launchOptions NS_DESIGNATED_INITIALIZER;

/// 禁用 init 初始化
- (instancetype)init NS_UNAVAILABLE;

/// 禁用 new 初始化
+ (instancetype)new NS_UNAVAILABLE;

/**
 * @abstract
 * 设置 flush 时网络发送策略
 *
 * @discussion
 * 默认 3G、4G、5G、WI-FI 环境下都会尝试 flush
 */
@property (nonatomic)QTNetworkType flushNetworkPolicy;

/**
 * @property
 *
 * @abstract
 * 两次数据发送的最小时间间隔，单位毫秒
 *
 * @discussion
 * 默认值为 3 * 1000 毫秒， 在每次调用 event 和 uploadUserProfile 等接口的时候，
 * 都会检查如下条件，以判断是否向服务器上传数据:
 * 1. 是否 WIFI/3G/4G/5G 网络
 * 2. 是否满足以下数据发送条件之一:
 *   1) 与上次发送的时间间隔是否大于 flushInterval
 *   2) 本地缓存日志数目是否超过 flushBulkSize
 * 如果满足这两个条件之一，则向服务器发送一次数据；如果都不满足，则把数据加入到队列中，等待下次检查时把整个队列的内容一并发送。
 * 需要注意的是，为了避免占用过多存储，队列最多只缓存TODO: 这里是否维持 10000 条数据。
 */
@property (nonatomic) NSInteger flushInterval;

/// 开启 log 打印
@property (nonatomic, assign) BOOL enableLog;

/// 禁用 SDK，默认为 NO
///
/// 禁用后，SDK 将不会触发事件，也不会发送网络请求
@property (nonatomic, assign) BOOL disableSDK;

/// App 进入后台时是否等待数据发送结果。默认 NO，不会等待数据发送结果；设置 YES，会等待数据发送结果
@property (nonatomic, assign) BOOL flushBeforeEnterBackground;

/// 自定义埋点数据存储路径
///
/// macOS 开发，针对多应用场景，可以使用相同数据库文件，确保每个应用触发 flush 后，上传所有埋点数据，使用 .plist 作为文件名后缀
@property (nonatomic, strong) NSString *dbFilePath API_UNAVAILABLE(ios, tvos);

/// 设置本地缓存最多事件条数，默认为 10000 条事件
@property (nonatomic) NSInteger maxCacheSize;

/// 是否禁用采集 deviceId
@property (nonatomic, assign) BOOL disableDeviceId;

/// 自定义埋点数据存储路径
///
/// macOS 开发，针对多应用场景，可以使用相同数据库文件，确保每个应用触发 flush 后，上传所有埋点数据，使用 .plist 作为文件名后缀
@property (nonatomic, strong) NSString *storeFilePath API_UNAVAILABLE(ios, tvos);

@end

NS_ASSUME_NONNULL_END
