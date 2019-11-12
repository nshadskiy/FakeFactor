import sys
sys.path.append("../CutObject")
from CutObject import Cut
sys.path.append("../Weights")
from Weights import Weight

class Era:

    def __init__(self, era, channel, shift = "NOMINAL"):

        if era == "2016_KIT_emb": # It is important that the "emb" is part of the era name if you want to use embedded samples
            # Cut.cutfile = "/home/jandrej/CMSSW_9_4_0/src/HephyHiggs/Tools/Datacard/conf2016/cuts.json"
            self.lumi = 35.87
            self.weights = "weight"
            self.tauidsfs = {
                "tight":  "0.95",
                "vtight": "0.95"
            }

            self.add_weights = self.weights.replace(" ","").split("*") 
            path = "/ceph/jbechtel/2016_v14/{0}-".format( channel)
            ext = ".root"

            self.mcSamples = [
                (path + shift + "_ntuple_WJets"+ext,"WJets",""),
                (path + shift + "_ntuple_EMB"+ext,"EMB",Cut("-GENTAU-") ),
                # (path + shift + "_ntuple_DY"+ext,"ZTT",Cut("-GENTAU-") ),
                (path + shift + "_ntuple_DY"+ext,"ZL", Cut("!(-GENTAU- | -GENJET-)") ),
                (path + shift + "_ntuple_DY"+ext,"ZJ", Cut("-GENJET-") ),
                # (path + shift + "_ntuple_TT"+ext,"TTT",Cut("-GENTAU-") ),
                (path + shift + "_ntuple_TT"+ext,"TTL",Cut("!(-GENTAU- | -GENJET-)") ),
                (path + shift + "_ntuple_TT"+ext,"TTJ",Cut("-GENJET-") ),
                # (path + shift + "_ntuple_VV"+ext,"VVT",Cut("-GENTAU-") ),
                (path + shift + "_ntuple_VV"+ext,"VVL",Cut("!(-GENTAU- | -GENJET-)") ),
                (path + shift + "_ntuple_VV"+ext,"VVJ",Cut("-GENJET-") ),
            ]
            self.dataSample = path + "NOMINAL_ntuple_Data"+ext
