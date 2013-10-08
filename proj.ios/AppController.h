#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

//接收从服务器返回数据。
@property (nonatomic,retain) NSMutableData *datas;

@end

