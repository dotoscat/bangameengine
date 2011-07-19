scene = bange.NewScene(1)
layerobject = scene:SetLayerObject(1, 1)
layerobject:AddText("Hi World!")

view = bange.NewView(640, 480)
view.scene = scene

bange.Scenes = {scene}
bange.Views = {view}
