scene = bange.NewScene(1)
layerobject = scene:SetLayerObject(1, 1)
text = layerobject:AddText("Hi World!")

view = bange.NewView(640, 480)
scene:AddView(view)

bange.Run = {scene}
