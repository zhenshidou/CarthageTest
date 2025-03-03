//
//  QTConstants.h
//  QuickTrackingSDK
//
//  Created by 钰昭 on 2025/1/1.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - typedef
/**
 * @abstract
 * Debug 模式，用于检验数据导入是否正确。该模式下，事件会逐条实时发送到 QuickTracking，并根据返回值检查
 * 数据导入是否正确。
 *
 * Debug模式有三种选项:
 *   QuickTrackingDebugOff - 关闭 DEBUG 模式
 *   QuickTrackingDebugOnly - 打开 DEBUG 模式，但该模式下发送的数据仅用于调试，不进行数据导入
 *   QuickTrackingDebugAndTrack - 打开 DEBUG 模式，并将数据上报到 QuickTracking 中
 */
typedef NS_ENUM(NSInteger, QuickTrackingDebugMode) {
    QuickTrackingDebugOff,
    QuickTrackingDebugOnly,
    QuickTrackingDebugAndTrack,
};

/**
 * @abstract
 * 网络类型
 *
 * @discussion
 *   QTNetworkTypeNONE - NULL
 *   QTNetworkType2G - 2G
 *   QTNetworkType3G - 3G
 *   QTNetworkType4G - 4G
 *   QTNetworkType5G - 5G
 *   QTNetworkTypeWIFI - WIFI
 *   QTNetworkTypeALL - ALL
 */
typedef NS_OPTIONS(NSInteger, QTNetworkType) {
    QTNetworkTypeNONE         = 0,
    QTNetworkType2G API_UNAVAILABLE(macos, tvos)    = 1 << 0,
    QTNetworkType3G API_UNAVAILABLE(macos, tvos)    = 1 << 1,
    QTNetworkType4G API_UNAVAILABLE(macos, tvos)    = 1 << 2,
    QTNetworkTypeWIFI     = 1 << 3,
    QTNetworkTypeALL      = 0xFF,
#ifdef __IPHONE_14_1
    QTNetworkType5G API_UNAVAILABLE(macos, tvos)   = 1 << 4
#endif
};

/// 事件类型
typedef NS_OPTIONS(NSUInteger, QTEventType) {
    QTEventTypeTrack = 1 << 0,
    QTEventTypeSignup = 1 << 1,

    QTEventTypeDefault = 0xF,
    QTEventTypeAll = 0xFFFFFFFF,
};

/// 页面模型相关
typedef NS_ENUM(int, QTPageModelType) {
    QTPageModelTypeNative = 0, //Native
    QTPageModelTypeH5,         //H5
    QTPageModelTypeHeader
};

typedef NS_ENUM(NSInteger, QTPageActionType) {
    QTPageActionTypeForword,        //后退(适用于native或h5)
    QTPageActionTypeBack,           //前进(适用于native或h5)
    QTPageActionTypeRefresh,        //刷新(适用于h5)
    //挂起状态(适用于native->h5 或者 h5->native的界面的时候)比如在跳转到native界面中，
    //嵌入h5的时候，如果h5里面发生调用，就切换到h5的PageModel,当前的native的PageModel
    //就处于PageActionTypePending的状态(只有pageBegin,没有pageEnd)
    QTPageActionTypePending
};

typedef NS_ENUM(NSInteger, QTPageModelState) {
    QTPageModelStateNone,              //后退(适用于native或h5)
    QTPageModelStateDisappear,         //处于隐藏状态
    //挂起状态(适用于native->h5 或者 h5->native的界面的时候)比如在跳转到native界面中，
    //嵌入h5的时候，如果h5里面发生调用，就切换到h5的PageModel,当前的native的PageModel
    //就处于PageActionTypePending的状态(只有pageBegin,没有pageEnd)
    QTPageModelStatePending,
    QTPageModelStateDeallocing,        //处于析构状态
    QTPageModelStateDealloced          //析构完成
};


NS_ASSUME_NONNULL_END
