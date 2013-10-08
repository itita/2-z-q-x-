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
            "targetOpacity" : "255"
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
            "targetOpacity" : "255"
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
                "content" : "　　该死！我们的前线基地被轰炸了，敌人闪电战已经突入我方纵深，我们被包围了！",
                "x" : 330,
                "y" : 190,
                "scaleX" : 1.2,
                "scaleY" : 1.2,
                "anchorX" : 0,
                "anchorY" : 1,
                "width" : -340,
                "dimensionsHeight" : 180,
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
            "targetOpacity" : "255"
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
            "targetOpacity" : "255"
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
            "duration" : 1,
            "targetOpacity" : "255"
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
            "targetOpacity" : "255"
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
                "content" : "　　无法联络到总部，新手，照顾好自己，我们要有麻烦了。必须先重新建立一个指挥中心。这个就交给你了，不要让我失望。",
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
        }
    ]
}