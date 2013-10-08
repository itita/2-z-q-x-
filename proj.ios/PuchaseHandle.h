//
//  PuchaseHandle.h
//  ww4
//
//  Created by xiao tang on 13-7-21.
//
//

#import <StoreKit/StoreKit.h>

@interface PuchaseHandle : NSObject {

    int buyType;
    int gameuserid;
    int gameserviceid;
    NSDecimalNumber* gameMoney;
    
    NSMutableArray *pacekt_ids;
    NSString *baseUrl;

}

+(PuchaseHandle *) sharedPuchaseHandle;


- (void) requestProUpgradeProductData;
-(void)RequestProductData;
-(bool)CanMakePay;
-(void)buy:(int)position  ServiceId:(int)serviceid UserId:(int)userid ;
-(BOOL)putStringToItunes:(NSData*)iapData;
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction;
- (void) completeTransaction: (SKPaymentTransaction *)transaction;
- (void) failedTransaction: (SKPaymentTransaction *)transaction;
-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction;
-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error;
- (void) restoreTransaction: (SKPaymentTransaction *)transaction;
-(void)provideContent:(NSString *)product;
-(void)recordTransaction:(NSString *)product;
@end
