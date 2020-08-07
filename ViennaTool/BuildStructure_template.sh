#!/bin/bash
user=$USER
fftype=2016


line=" -------------------------------------------"
echo "###### START of BuildStructure.sh ######"
echo $line
echo "Starting $fftype analysis"
echo "Group CMS-HTT"
echo "Hephy Vienna"
echo $line

echo "Buidling folder structure"

if [ -d "/ceph/$user/auto-testing-fakefactors/$fftype/preselection" ]; then
    if [ ! -d "/ceph/$user/auto-testing-fakefactors/$fftype/preselection/mt" ]; then
        mkdir -p /ceph/$user/auto-testing-fakefactors/$fftype/preselection/mt
    fi
    if [ ! -d "/ceph/$user/auto-testing-fakefactors/$fftype/preselection/et" ]; then
        mkdir -p /ceph/$user/auto-testing-fakefactors/$fftype/preselection/et
    fi
    if [ ! -d "/ceph/$user/auto-testing-fakefactors/$fftype/preselection/tt" ]; then
        mkdir -p /ceph/$user/auto-testing-fakefactors/$fftype/preselection/tt
    fi
else
    mkdir -p /ceph/$user/auto-testing-fakefactors/$fftype/preselection/mt
    mkdir -p /ceph/$user/auto-testing-fakefactors/$fftype/preselection/et
    mkdir -p /ceph/$user/auto-testing-fakefactors/$fftype/preselection/tt
fi
mkdir -p /ceph/$user/auto-testing-fakefactors/$fftype/preselection/mt


if [ -d "sim" ]; then
    if [ ! -d "sim/mt" ]; then
        mkdir -p sim/mt
    fi
    if [ ! -d "sim/et" ]; then
        mkdir -p sim/et
    fi
    if [ ! -d "sim/tt" ]; then
        mkdir -p sim/tt
    fi
else
    mkdir -p sim/mt
    mkdir -p sim/et
    mkdir -p sim/tt
fi

if [ -d "Images_EMB" ]; then
    if [ ! -d "Images_EMB/data_mt_EMB" ]; then
        mkdir -p Images_EMB/data_mt
    fi
    if [ ! -d "Images_EMB/data_et_EMB" ]; then
        mkdir -p Images_EMB/data_et
    fi
    if [ ! -d "Images_EMB/data_tt_EMB" ]; then
        mkdir -p Images_EMB/data_tt
    fi
    if [ ! -d "Images_EMB/mc_mt" ]; then
        mkdir -p Images_EMB/mc_mt
    fi
    if [ ! -d "Images_EMB/mc_et" ]; then
        mkdir -p Images_EMB/mc_et
    fi
    if [ ! -d "Images_EMB/mc_tt" ]; then
        mkdir -p Images_EMB/mc_tt
    fi
    if [ ! -d "Images_EMB/mc_woQCD_mt" ]; then
        mkdir -p Images_EMB/mc_woQCD_mt
    fi
    if [ ! -d "Images_EMB/mc_woQCD_et" ]; then
        mkdir -p Images_EMB/mc_woQCd_et
    fi
    if [ ! -d "Images_EMB/mc_woQCD_tt" ]; then
        mkdir -p Images_EMB/mc_woQCd_tt
    fi
    
    
else
    mkdir -p Images_EMB
    mkdir -p Images_EMB/data_mt
    mkdir -p Images_EMB/data_et
    mkdir -p Images_EMB/data_tt
    mkdir -p Images_EMB/mc_mt
    mkdir -p Images_EMB/mc_et
    mkdir -p Images_EMB/mc_tt
    mkdir -p Images_EMB/mc_woQCD_mt
    mkdir -p Images_EMB/mc_woQCD_et
    mkdir -p Images_EMB/mc_woQCD_tt
fi
if [ -d "Images_NonEMB" ]; then
    if [ ! -d "Images_NonEMB/data_mt_EMB" ]; then
        mkdir -p Images_NonEMB/data_mt
    fi
    if [ ! -d "Images_NonEMB/data_et_EMB" ]; then
        mkdir -p Images_NonEMB/data_et
    fi
    if [ ! -d "Images_NonEMB/data_tt_EMB" ]; then
        mkdir -p Images_NonEMB/data_tt
    fi
    if [ ! -d "Images_NonEMB/mc_mt" ]; then
        mkdir -p Images_NonEMB/mc_mt
    fi
    if [ ! -d "Images_NonEMB/mc_et" ]; then
        mkdir -p Images_NonEMB/mc_et
    fi
    if [ ! -d "Images_NonEMB/mc_tt" ]; then
        mkdir -p Images_NonEMB/mc_tt
    fi
    if [ ! -d "Images_NonEMB/mc_woQCD_mt" ]; then
        mkdir -p Images_NonEMB/mc_woQCD_mt
    fi
    if [ ! -d "Images_NonEMB/mc_woQCD_et" ]; then
        mkdir -p Images_NonEMB/mc_woQCd_et
    fi
    if [ ! -d "Images_NonEMB/mc_woQCD_tt" ]; then
        mkdir -p Images_NonEMB/mc_woQCd_tt
    fi
    
    
else
    mkdir -p Images_NonEMB
    mkdir -p Images_NonEMB/data_mt
    mkdir -p Images_NonEMB/data_et
    mkdir -p Images_NonEMB/data_tt
    mkdir -p Images_NonEMB/mc_mt
    mkdir -p Images_NonEMB/mc_et
    mkdir -p Images_NonEMB/mc_tt
    mkdir -p Images_NonEMB/mc_woQCD_mt
    mkdir -p Images_NonEMB/mc_woQCD_et
    mkdir -p Images_NonEMB/mc_woQCD_tt
fi

if [ -d "fakefactor" ]; then
    if [ ! -d "fakefactor/data_mt" ]; then
        mkdir -p fakefactor/data_mt
    fi
    if [ ! -d "fakefactor/data_et" ]; then
        mkdir -p fakefactor/data_et
    fi
    if [ ! -d "fakefactor/data_tt" ]; then
        mkdir -p fakefactor/data_tt
    fi
    if [ ! -d "fakefactor/mc_mt" ]; then
        mkdir -p fakefactor/mc_mt
    fi
    if [ ! -d "fakefactor/mc_et" ]; then
        mkdir -p fakefactor/mc_et
    fi
    if [ ! -d "fakefactor/mc_tt" ]; then
        mkdir -p fakefactor/mc_tt
    fi
    if [ ! -d "fakefactor/mc_woQCD_mt" ]; then
        mkdir -p fakefactor/mc_woQCD_mt
    fi
    if [ ! -d "fakefactor/mc_woQCD_et" ]; then
        mkdir -p fakefactor/mc_woQCd_et
    fi
    if [ ! -d "fakefactor/mc_woQCD_tt" ]; then
        mkdir -p fakefactor/mc_woQCd_tt
    fi
    
else
    mkdir -p fakefactor/data_mt
    mkdir -p fakefactor/data_et
    mkdir -p fakefactor/data_tt
    mkdir -p fakefactor/mc_mt
    mkdir -p fakefactor/mc_et
    mkdir -p fakefactor/mc_tt
    mkdir -p fakefactor/mc_woQCD_mt
    mkdir -p fakefactor/mc_woQCD_et
    mkdir -p fakefactor/mc_woQCD_tt
fi

if [ ! -d "ff_2d" ]; then
    if [ ! -d "ff_2d/mt" ]; then
        if [ ! -d "ff_2d/mt/incl" ]; then
            mkdir -p ff_2d/mt/incl;
        fi
        if [ ! -d "ff_2d/mt/_dummycat" ]; then
            mkdir -p ff_2d/mt/_dummycat;
        fi
        
    else
        mkdir -p ff_2d/mt/incl;
        mkdir -p ff_2d/mt/_dummycat;
    fi
    if [ ! -d "ff_2d/et" ]; then
        if [ ! -d "ff_2d/et/incl" ]; then
            mkdir -p ff_2d/et/incl;
        fi
        if [ ! -d "ff_2d/et/_dummycat" ]; then
            mkdir -p ff_2d/et/_dummycat;
        fi        
    else
        mkdir -p ff_2d/et/incl;
        mkdir -p ff_2d/et/_dummycat;
    fi
    if [ ! -d "ff_2d/tt" ]; then
        if [ ! -d "ff_2d/tt/incl" ]; then
            mkdir -p ff_2d/tt/incl;
        fi
        if [ ! -d "ff_2d/tt/_dummycat" ]; then
            mkdir -p ff_2d/tt/_dummycat;
        fi        
    else
        mkdir -p ff_2d/tt/incl;
        mkdir -p ff_2d/tt/_dummycat;
    fi
    
    
else
    mkdir -p ff_2d/mt/incl;
    mkdir -p ff_2d/mt/_dummycat;
    mkdir -p ff_2d/et/incl;
    mkdir -p ff_2d/et/_dummycat;
    mkdir -p ff_2d/tt/incl;
    mkdir -p ff_2d/tt/_dummycat;
fi



echo "###### END of BuildStructure.sh ######"
