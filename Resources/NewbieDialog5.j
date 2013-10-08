{
    "creatorPriority": -601,
    "pvrName" : "campaignSheet",
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
                "content" : "　　装甲集团已经到达，敌军营地后方防守薄弱，派遣装甲部队从后方包抄！",
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
             "duration" : 0.2,
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
             "duration" : 0.2,
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
             "duration" : 0.2,
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
             "duration" : 0.2,
             "targetOpacity" : 255
          }
      }
                }
            ]
        }
    ]
}