package name.wwd.update;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class PurchaseActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

//		EgameFee.init(this, new EgameFeeResultListener() {
//			@Override
//			public void egameFeeSucceed(int gameUserId, int feeMoney,
//					EgameFeeChannel feeChannel) {
//				System.out.println("egameFeeSucceed");
//				// 用户充值成功，在这里可以刷新用户金币数
//			}
//
//			@Override
//			public void egameFeeCancel() {
//				System.out.println("egameFeeCancel");
//				// 用户取消充值
//			}
//
//			@Override
//			public void egameFeeFailed() {
//				System.out.println("egameFeeFailed");
//				// 充值失败
//			}
//		});
//		EgameFee.pay(123456, 1);
////		/**
////		 * 1. 普通充值
////		 * 调用后会打开计费SDK充值渠道选择界面，如果手机卡为电信卡并且是短代支持的计费代码则会显示话费支付选项，否则不会出现话费支付选项
////		 * ；第三方支付会根据计费代码进行筛选，只会显示支持此计费代码的充值渠道。 EgameFee.pay(123456, 1);
////		 * //调用此方法后会打开计费SDK界面进行充值 //
////		 * 123456-gameUserId游戏用户编号,此编号为用户自定义的1~268435455的10进制整数,也可以是游戏自定义的流水号 //
////		 * 1-计费金额，用户选择的充值金额
////		 */
////		this.btnCommonChongzhi.setOnClickListener(new OnClickListener() {
////
////			@Override
////			public void onClick(View v) {
////				
////			}
////		});
////
////		/**
////		 * 2. 短代快速充值
////		 * 优先话费支付，如果计费代码不是短代支持的计费代码则无法快速完成充值，在无法快速充值时会根据第3个参数来判断是否选择普通充值
////		 * EgameFee.payBySms(123456, 1,true); //
////		 * 123456-gameUserId游戏用户编号,此编号为用户自定义的1~268435455的10进制整数,也可以是游戏自定义的流水号 //
////		 * 1-计费金额，用户选择的充值金额 // true –
////		 * 如果这里参数值为true，那么如果用户手机不是电信卡或者计费代码不是短代支持的计费代码那么会调用普通充值进行充值
////		 * ，如果这里参数为false，那么如果用户手机不是电信卡或者计费代码不是短代支持的计费代码则不会调用普通充值进行充值
////		 */
////		this.btnDuandaiKuaisuChongzhi.setOnClickListener(new OnClickListener() {
////
////			@Override
////			public void onClick(View v) {
////				EgameFee.payBySms(123456, 1, true);
////			}
////		});
//
//		
	}

	
}
