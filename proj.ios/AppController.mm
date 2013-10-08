#import "AppController.h"
#import "EAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the EAGLView
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGB565
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    cocos2d::CCApplication::sharedApplication()->run();

    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:
     (UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert)];
    
    return YES;
}

- (void)application:(UIApplication*)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken
{
	//NSLog(@"My token is: %@", deviceToken);
    
    //获得 device token
    NSLog(@"deviceToken: %@", deviceToken);
    //在这里把deviceToken和用户信息发送到服务器端
    
    
    NSUserDefaults* userDefaults = [NSUserDefaults standardUserDefaults];
    id resgisterSucc = [userDefaults valueForKey:@"resgisterSucc"];
    if(resgisterSucc != nil){
        bool succ = [resgisterSucc boolValue];
        if(succ){
            NSLog(@"已经向服务器注册过了，不需要重新注册");
            return;
        }
    }
    //请求地址
    NSString *urlString = [NSString stringWithFormat:@"http://121.199.27.213:81/WWApns/registerDevice?deviceToken=%@",deviceToken ];
    
    
    NSString* newUrl = [[[urlString stringByReplacingOccurrencesOfString:@" " withString:@""]stringByReplacingOccurrencesOfString:@"<" withString:@""] stringByReplacingOccurrencesOfString:@">" withString:@""];
    
    NSLog(@"上传URL:%@",newUrl);
    
    //第一步，创建url
    NSURL *url = [NSURL URLWithString:newUrl];
    
    NSURLRequest *request = [[NSURLRequest alloc] initWithURL:url];
    NSURLConnection *connection = [[NSURLConnection alloc]
                                   initWithRequest:request
                                   delegate:self];
    if (connection) {
        _datas = [NSMutableData new];
    }
    
    //    [urlString release];
    //    [url release];
    //    [request release];
    //    [connection release];
    
}

// #####################################################################################

#pragma mark- NSURLConnection 回调方法
//接收到服务器传输数据的时候调用，此方法根据数据大小执行若干次
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
    [_datas appendData:data];
}

//网络请求过程中，出现任何错误（断网，连接超时等）会进入此方法
-(void) connection:(NSURLConnection *)connection didFailWithError: (NSError *)error {
    NSLog(@"%@",[error localizedDescription]);
    if(_datas != nil) {
        [_datas release];
        _datas = nil;
    }
}

//数据传完之后调用此方法
- (void) connectionDidFinishLoading: (NSURLConnection*) connection {
    NSLog(@"请求完成…");
    
    
    //1. 字符串格式
    
    NSString * strData1= [[NSString alloc] initWithData:_datas encoding:NSUTF8StringEncoding];
    NSLog(@"收到的UTF8数据:%@",strData1);
    
    
    
    NSDictionary* dict = [NSJSONSerialization JSONObjectWithData:_datas
                          
                                                         options:NSJSONReadingAllowFragments error:nil];
    NSLog(@"收到的数据:%@",dict);
    id succ = [dict valueForKey:@"succ"];
    
    NSLog(@"%@",succ);
    
    if([succ boolValue]){
        NSString *valueToSave = [succ stringValue];
        [[NSUserDefaults standardUserDefaults]
         setObject:valueToSave forKey:@"resgisterSucc"];
    }
    
    //
    //    [dict release];
    [strData1 release];
    [_datas release];
    _datas = nil;
}

//######################################################################################







- (void)application:(UIApplication*)application didFailToRegisterForRemoteNotificationsWithError:(NSError*)error
{
	NSLog(@"Failed to get token, error: %@", error);
    if(_datas != nil) {
        [_datas release];
        _datas = nil;
    }
}


- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    /*
     
     收到消息自定义事件
     
     */
    
    if ([[userInfo objectForKey:@"aps"] objectForKey:@"alert"] != nil) {
        
        //        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"通知"
        //                                                        message:[[userInfo objectForKey:@"aps"] objectForKey:@"alert"]
        //                                                       delegate:self
        //                                              cancelButtonTitle:@"确定"
        //                                              otherButtonTitles:nil];
        //        [alert show];
        //        [alert release];
        
        
        //
        [UIApplication sharedApplication].applicationIconBadgeNumber = 0;
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
    }
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
