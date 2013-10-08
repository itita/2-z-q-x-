//
//  PuchaseHandle.m
//  ww4
//
//  Created by xiao tang on 13-7-21.
//
//

#import "PuchaseHandle.h"
#import "PurchaseAddtion.h"


@implementation PuchaseHandle


static PuchaseHandle *sharedRootController = nil;

+(PuchaseHandle *) sharedPuchaseHandle{
    @synchronized(self){
        if (sharedRootController == nil) {
            sharedRootController = [[self alloc] init] ;
            [sharedRootController initProduct];
        }
    }
    return  sharedRootController;
}

-(void)initProduct {
    pacekt_ids=[[NSMutableArray alloc]initWithCapacity:10];//指定有五个元素初始化
    pacekt_ids[0]=@"com.itita.wwdz_shuijin600";
    pacekt_ids[1]=@"com.itita.wwdz_shuijin3150";
    pacekt_ids[2]=@"com.itita.wwdz_shuijin7480";
    pacekt_ids[3]=@"com.itita.wwdz_shuijin14720";
    pacekt_ids[4]=@"com.itita.wwdz_shuijin39630";
    pacekt_ids[5]=@"com.itita.wwdz_shuijin84240";
    baseUrl=@"http://121.199.27.213:81/game/applepay";
}

-(void)buy:(int)position  ServiceId:(int)serviceid UserId:(int)userid
{
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    buyType = position;
    gameuserid=userid;
    gameserviceid=serviceid;
    if ([SKPaymentQueue canMakePayments]) {
        //[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
        [self RequestProductData];
//        CCLOG(@"允许程序内付费购买");
    }
    else
    {
//        CCLOG(@"不允许程序内付费购买");
        UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"提示"
                                                            message:@"You can‘t purchase in app store（错误的购买码）"
                                                           delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
        
        [alerView show];
        [alerView release];
        
    }
}


-(void)RequestProductData
{
//    CCLOG(@"---------请求对应的产品信息------------");
    NSArray *product = nil;
    
    product=[[NSArray alloc] initWithObjects:pacekt_ids[buyType],nil];
    
    NSSet *nsset = [NSSet setWithArray:product];
    SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers: nsset];
    request.delegate=self;
    [request start];
    [product release];
}


//<SKProductsRequestDelegate> 请求协议
//收到的产品信息
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    
//    NSLog(@"-----------收到产品反馈信息--------------");
    NSArray *myProduct = response.products;
//    NSLog(@"产品Product ID:%@",response.invalidProductIdentifiers);
//    NSLog(@"产品付费数量: %d", [myProduct count]);
    // populate UI
    for(SKProduct *product in myProduct){
//        NSLog(@"product info");
//        NSLog(@"SKProduct 描述信息%@", [product description]);
//        NSLog(@"产品标题 %@" , product.localizedTitle);
//        NSLog(@"产品描述信息: %@" , product.localizedDescription);
//        NSLog(@"价格: %@" , product.price);
        if(gameMoney != nil) {
            [gameMoney release];
            gameMoney = nil;
        }
        gameMoney = [product.price copy];
//        NSLog(@"Product id: %@" , product.productIdentifier);
    }
    SKPayment *payment = nil;
    payment  =[SKPayment paymentWithProductIdentifier:pacekt_ids[buyType]];
    
    
//    CCLOG(@"---------发送购买请求------------");
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    [request autorelease];
    
}
- (void)requestProUpgradeProductData
{
//    CCLOG(@"------请求升级数据---------");
    NSSet *productIdentifiers = [NSSet setWithObject:@"com.productid"];
    SKProductsRequest* productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    productsRequest.delegate = self;
    [productsRequest start];
    
}
//弹出错误信息
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error{
//    CCLOG(@"-------弹出错误信息----------");
    UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Alert",NULL) message:[error localizedDescription]
                                                       delegate:nil cancelButtonTitle:NSLocalizedString(@"Close",nil) otherButtonTitles:nil];
    [alerView show];
    [alerView release];
}

-(void) requestDidFinish:(SKRequest *)request
{
//    NSLog(@"----------反馈信息结束--------------:%@",request);
    
}

-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction{
//    CCLOG(@"-----PurchasedTransaction----%@",transaction);
    NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];
    [self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];
    [transactions release];
}

//<SKPaymentTransactionObserver> 千万不要忘记绑定，代码如下：
//----监听购买结果
//[[SKPaymentQueue defaultQueue] addTransactionObserver:self];

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions//交易结果
{
//    CCLOG(@"-----paymentQueue--------");
    
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased://交易完成
                
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed://交易失败
                [self failedTransaction:transaction];
//                CCLOG(@"-----交易失败 --------");
                UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle:@"提示"
                                                                     message:@"购买失败，请重新尝试购买～"
                                                                    delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
                
                [alerView2 show];
                [alerView2 release];
                break;
            case SKPaymentTransactionStateRestored://已经购买过该商品
                [self restoreTransaction:transaction];
//                CCLOG(@"-----已经购买过该商品 --------");
                
            case SKPaymentTransactionStatePurchasing:      //商品添加进列表
//                CCLOG(@"-----商品添加进列表 --------");
                break;
            default:
                break;
        }
    }
    
}
//交易结束了 将订单传入服务器端进行校验，并且发送
- (void) completeTransaction: (SKPaymentTransaction *)transaction

{
//    CCLOG(@"-----completeTransaction--------");
    
    
    // Your application should implement these two methods.
    NSString *product = transaction.payment.productIdentifier;
    if ([product length] > 0) {
        
        NSArray *tt = [product componentsSeparatedByString:@"."];
        NSString *bookid = [tt lastObject];
        if ([bookid length] > 0) {
            [self recordTransaction:bookid];
            [self provideContent:bookid];
            
            if([self
                putStringToItunes:transaction.transactionReceipt]){
                
                UIAlertView *alerView =  [[UIAlertView alloc] initWithTitle:@"提示"
                                                                    message:@"购买成功"
                                                                   delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
                
                [alerView show];
                [alerView release];
                
            }else{
                UIAlertView *alerView2 =  [[UIAlertView alloc] initWithTitle:@"Alert"
                                                                     message:@"购买失败，请重新尝试购买～"
                                                                    delegate:nil cancelButtonTitle:NSLocalizedString(@"Close（关闭）",nil) otherButtonTitles:nil];
                
                [alerView2 show];
                [alerView2 release];
            }
        }
    }
    
    
    
    // Remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    [PurchaseAddtion sendRemoveWaitLayerMsg];
    
}


-(BOOL)putStringToItunes:(NSData*)iapData{//用户购成功的transactionReceipt
    
    
//    CCLOG(@"-----长度 --------%d",[iapData length]);
    
    NSString* result = [iapData base64String];
//    result
    
    
//    CCLOG(@"-----订单回执信息 --------%@",result);
    
    
    NSURL *url = [NSURL URLWithString:baseUrl];
    //第二步，创建请求
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:30];
    [request setHTTPMethod:@"POST"];//设置请求方式为POST，默认为GET
    
    
    NSString *postString = [NSString stringWithFormat:@"receipt-data=%@&userid=%d&serviceid=%d&gamemoney=%@",result,gameuserid,gameserviceid,gameMoney];
    //将post数据转换为 NSASCIIStringEncoding 编码格式
    NSData *postData = [postString dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:YES];
    [request setHTTPBody:postData];
    
    
    
    
    
    NSHTTPURLResponse
    *urlResponse=nil;
    
    NSError
    *errorr=nil;
    
    NSData
    *receivedData = [NSURLConnection sendSynchronousRequest:request
                     
                                          returningResponse:&urlResponse
                     
                                                      error:&errorr];
    
    
    
    //解析
    
//    NSString   *results=[[NSString alloc]initWithBytes:[receivedData bytes] length:[receivedData length] encoding:NSUTF8StringEncoding];
    
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];//解除监听
    
//    CCLOG(@"返回状态 %@",results);
    //
    //          NSDictionary*dic
    //          = [results JSONValue];
    //
    //          if([[dic
    //               objectForKey:@"status"]
    //              intValue]==0){//注意，status=@"0"是验证收据成功
    //
    //        return
    //        true;
    //
    //    }
    
    
    
    return
    true;
    
}



//记录交易
-(void)recordTransaction:(NSString *)product{
//    CCLOG(@"-----记录交易--------%@",product);
}

//处理下载内容
-(void)provideContent:(NSString *)product{
//    CCLOG(@"-----下载--------%@",product);
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction{
    NSLog(@"失败");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
    }
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    [PurchaseAddtion sendRemoveWaitLayerMsg];
    
}
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction{
    
}

- (void) restoreTransaction: (SKPaymentTransaction *)transaction

{
    NSLog(@" 交易恢复处理");
    
}

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error{
//    CCLOG(@"-------paymentQueue----");
}

// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
    
	[[SKPaymentQueue defaultQueue] removeTransactionObserver:self];//解除监听
    
	[super dealloc];
}


@end
