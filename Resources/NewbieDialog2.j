{
    "creatorPriority": -500,
    "pvrName" : "campaignSheet",
    "nextNodeSfx" : "sfx_click.mp3",
    "initSprites" : [
        {
            "frameName":"whiteImage.png",
            "anchorY" : 0,
            "y" : -10,
            "r" : 18,
            "g" : 13,
            "b" : 13,
            "scaleX" : 60,
            "scaleY" : 10.5,
            "relativeType" : 1,
            "a" : 230,
    "action" : {
        "fadeTo" : {
            "duration" : 0.2,
            "targetOpacity" : 255
        }
    }
        },
        {
            "frameName":"dialogLine.png",
            "y" : 196,
            "scaleX" : 40,
            "relativeType" : 1,
            "a" : 255,
    "action" : {
        "fadeTo" : {
            "duration" : 0.2,
            "targetOpacity" : 255
        }
    }
        }
    ],
    "talkNodes" : [
        {
            "content": {
                "content" : "　　这里显示头像、昵称、等级、还有经验。",
                "x" : 8,
                "y" : 190,
                "size" : 30,
                "anchorX" : 0,
                "anchorY" : 1,
                "dimensionsWidth" : -8,
                "dimensionsHeight" : 180,
                "relativeDWidthType" : 2
            }
        },
        {
            "content": {
                "content" : "　　这里显示你所拥有的资源。石油主要用于军事，钢铁主要用于建设，功勋主要用于部队升级。",
                "x" : 8,
                "y" : 190,
                "size" : 30,
                "anchorX" : 0,
                "anchorY" : 1,
                "dimensionsWidth" : -8,
                "dimensionsHeight" : 180,
                "relativeDWidthType" : 2
            }
        },
        {
            "content": {
                "content" : "　　中间就是基地部分，可以在地图上任意建设。",
                "x" : 8,
                "y" : 190,
                "size" : 30,
                "anchorX" : 0,
                "anchorY" : 1,
                "dimensionsWidth" : -8,
                "dimensionsHeight" : 180,
                "relativeDWidthType" : 2
            }
        }
    ]
}