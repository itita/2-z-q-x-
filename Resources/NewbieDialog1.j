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
            "a" : 240,
            "action" : {
                "fadeTo" : {
                    "duration" : 0.5,
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
                    "duration" : 0.5,
                    "targetOpacity" : 255
                }
            }
        }
    ],
    "talkNodes" : [
        {
            "name": {
                "content" : "艾伦少校",
                "x" : 305,
                "y" : 245,
                "size" : 30,
                "r" : 255,
                "g" : 222,
                "b" : 0
            },
            "content": {
                "content" : "　　嘿，伙计！我是你的上司，陆军航空队第八大队少校，这个基地的总指挥，约瑟夫 艾伦。",
                "x" : 330,
                "y" : 190,
                "scaleX" : 1.2,
                "scaleY" : 1.2,
                "anchorX" : 0,
                "anchorY" : 1,
                "width" : -340,
                "relativeDWidthType" : 2
            },
            "icons" : [
                {
                    "frameName":"JosephAllen.png",
                    "anchorX" : 0,
                    "anchorY" : 0,
                    "action" : {
                        "fadeTo" : {
                            "duration" : 0.5,
                            "targetOpacity" : 255
                        }
                    }
                },
                {
                    "frameName":"nameKuangCenter.png",
                    "x" : 322,
                    "y" : 250,
                    "scaleX" : 1.1,
                    "anchorX" : 0.5,
                    "action" : {
                        "fadeTo" : {
                            "duration" : 0.5,
                            "targetOpacity" : 255
                        }
                    }
                },
                {
                    "frameName":"nameKuangLeft.png",
                    "x" : 292,
                    "y" : 250,
                    "anchorX" : 1,
                    "action" : {
                        "fadeTo" : {
                            "duration" : 0.5,
                            "targetOpacity" : 255
                        }
                    }
                },
                {
                    "frameName":"nameKuangRight.png",
                    "x" : 355,
                    "y" : 250,
                    "anchorX" : 0,
                    "action" : {
                        "fadeTo" : {
                            "duration" : 0.5,
                            "targetOpacity" : 255
                        }
                    }
                }
            ]
        },
         {
            "name": {
                "content" : "艾伦少校",
                "x" : 305,
                "y" : 245,
                "size" : 30,
                "r" : 255,
                "g" : 222,
                "b" : 0
            },
            "content": {
                "content" : "　　目前战争形势还很严峻，没时间闲话了。首先，我来帮助你熟悉一下基地的管理。",
                "x" : 330,
                "y" : 190,
                "scaleX" : 1.2,
                "scaleY" : 1.2,
                "anchorX" : 0,
                "anchorY" : 1,
                "width" : -340,
                "relativeDWidthType" : 2
            },
            "icons" : [
                {
                    "frameName":"JosephAllen.png",
                    "anchorX" : 0,
                    "anchorY" : 0
                },
                {
                    "frameName":"nameKuangCenter.png",
                    "x" : 322,
                    "y" : 250,
                    "scaleX" : 1.1,
                    "anchorX" : 0.5
                },
                {
                    "frameName":"nameKuangLeft.png",
                    "x" : 292,
                    "y" : 250,
                    "anchorX" : 1
                },
                {
                    "frameName":"nameKuangRight.png",
                    "x" : 355,
                    "y" : 250,
                    "anchorX" : 0
                }
            ]
        },
         {
            "content": {
                "content" : "　　这里显示头像、昵称、等级、还有经验。",
                "x" : 8,
                "y" : 190,
                "scaleX" : 1.2,
                "scaleY" : 1.2,
                "anchorX" : 0,
                "anchorY" : 1,
                "width" : -8,
                "relativeDWidthType" : 2
            }
        },
        {
            "content": {
                "content" : "　　这里显示你所拥有的资源。石油主要用于军事，钢铁主要用于建设，功勋主要用于部队升级。",
                "x" : 8,
                "y" : 190,
                "scaleX" : 1.2,
                "scaleY" : 1.2,
                "anchorX" : 0,
                "anchorY" : 1,
                "width" : -8,
                "relativeDWidthType" : 2
            }
        },
        {
            "content": {
                "content" : "　　这里显示可以进行的基地操作，分别是建造，特权，部队。",
                "x" : 8,
                "y" : 190,
                "scaleX" : 1.2,
                "scaleY" : 1.2,
                "anchorX" : 0,
                "anchorY" : 1,
                "width" : -8,
                "relativeDWidthType" : 2
            }
        },
        {
            "content": {
                "content" : "　　中间就是基地部分，可以在地图上任意建设。",
                "x" : 8,
                "y" : 190,
                "scaleX" : 1.2,
                "scaleY" : 1.2,
                "anchorX" : 0,
                "anchorY" : 1,
                "width" : -8,
                "relativeDWidthType" : 2
            }
        }
    ]
}