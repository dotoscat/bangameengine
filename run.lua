scene = bange.NewScene(1)
layerobject = scene:SetLayerObject(1, 2)
--text = layerobject:AddText("Hi World!")

layerobject:AddShapeCircle({32, 32}, 8, {255, 255, 255})
--layerobject:AddShapeCircle({64, 32}, 8, {255, 255, 255})

view = bange.NewView(640, 480)
scene:AddView(view)

bange.Run = {scene}
