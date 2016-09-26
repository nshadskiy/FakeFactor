#!/bin/bash
user=jbrandstetter
fftype=FakeFactor_2015

line=" --------------------------------------------------------------------------------------"
echo $line
echo "Starting $fftype analysis"
echo "Group CMS-HTT"
echo "Hephy Vienna"
echo $line

if [ -d "/data/$user/$fftype/preselection" ]; then
    if [ ! -d "/data/$user/$fftype/preselection/mt" ]; then
        mkdir -p /data/$user/$fftype/preselection/mt
    fi
    if [ ! -d "/data/$user/$fftype/preselection/et" ]; then
        mkdir -p /data/$user/$fftype/preselection/et
    fi
    if [ ! -d "/data/$user/$fftype/preselection/tt" ]; then
        mkdir -p /data/$user/$fftype/preselection/tt
    fi
else
    mkdir -p /data/$user/$fftype/preselection/mt
    mkdir -p /data/$user/$fftype/preselection/et
    mkdir -p /data/$user/$fftype/preselection/tt
fi

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

if [ -d "Images" ]; then
    if [ ! -d "Images/data_mt" ]; then
        mkdir -p Images/data_mt
    fi
    if [ ! -d "Images/data_et" ]; then
        mkdir -p Images/data_et
    fi
    if [ ! -d "Images/data_tt" ]; then
        mkdir -p Images/data_tt
    fi
    if [ ! -d "Images/mc_mt" ]; then
        mkdir -p Images/mc_mt
    fi
    if [ ! -d "Images/mc_et" ]; then
        mkdir -p Images/mc_et
    fi
    if [ ! -d "Images/mc_tt" ]; then
        mkdir -p Images/mc_tt
    fi
    if [ ! -d "Images/mc_woQCD_mt" ]; then
        mkdir -p Images/mc_woQCD_mt
    fi
    if [ ! -d "Images/mc_woQCD_et" ]; then
        mkdir -p Images/mc_woQCd_et
    fi
    if [ ! -d "Images/mc_woQCD_tt" ]; then
        mkdir -p Images/mc_woQCd_tt
    fi
    
    
else
    mkdir -p Images/data_mt
    mkdir -p Images/data_et
    mkdir -p Images/data_tt
    mkdir -p Images/mc_mt
    mkdir -p Images/mc_et
    mkdir -p Images/mc_tt
    mkdir -p Images/mc_woQCD_mt
    mkdir -p Images/mc_woQCD_et
    mkdir -p Images/mc_woQCD_tt
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
        if [ ! -d "ff_2d/mt/_0jet" ]; then
            mkdir -p ff_2d/mt/_0jet;
        fi
        if [ ! -d "ff_2d/mt/_1jet" ]; then
            mkdir -p ff_2d/mt/_1jet;
        fi
        if [ ! -d "ff_2d/mt/_1jetZ050" ]; then
            mkdir -p ff_2d/mt/_1jetZ050;
        fi
        if [ ! -d "ff_2d/mt/_1jetZ50100" ]; then
            mkdir -p ff_2d/mt/_1jetZ50100;
        fi
        if [ ! -d "ff_2d/mt/_1jetZ100" ]; then
            mkdir -p ff_2d/mt/_1jetZ100;
        fi
        if [ ! -d "ff_2d/mt/_2jet" ]; then
            mkdir -p ff_2d/mt/_2jet;
        fi
        if [ ! -d "ff_2d/mt/_2jetVBF" ]; then
            mkdir -p ff_2d/mt/_2jetVBF;
        fi
        if [ ! -d "ff_2d/mt/_anyb" ]; then
            mkdir -p ff_2d/mt/_anyb;
        fi
    else
        mkdir -p ff_2d/mt/incl;
        mkdir -p ff_2d/mt/_0jet;
        mkdir -p ff_2d/mt/_1jet;
        mkdir -p ff_2d/mt/_1jetZ050;
        mkdir -p ff_2d/mt/_1jetZ50100;
        mkdir -p ff_2d/mt/_1jetZ100;
        mkdir -p ff_2d/mt/_2jet;
        mkdir -p ff_2d/mt/_2jetVBF;
        mkdir -p ff_2d/mt/_anyb;
    fi
    if [ ! -d "ff_2d/et" ]; then
        if [ ! -d "ff_2d/et/incl" ]; then
            mkdir -p ff_2d/et/incl;
        fi
        if [ ! -d "ff_2d/et/_0jet" ]; then
            mkdir -p ff_2d/et/_0jet;
        fi
        if [ ! -d "ff_2d/et/_1jet" ]; then
            mkdir -p ff_2d/et/_1jet;
        fi
        if [ ! -d "ff_2d/et/_1jetZ050" ]; then
            mkdir -p ff_2d/et/_1jetZ050;
        fi
        if [ ! -d "ff_2d/et/_1jetZ50100" ]; then
            mkdir -p ff_2d/et/_1jetZ50100;
        fi
        if [ ! -d "ff_2d/et/_1jetZ100" ]; then
            mkdir -p ff_2d/et/_1jetZ100;
        fi
        if [ ! -d "ff_2d/et/_2jet" ]; then
            mkdir -p ff_2d/et/_2jet;
        fi
        if [ ! -d "ff_2d/et/_2jetVBF" ]; then
            mkdir -p ff_2d/et/_2jetVBF;
        fi
        if [ ! -d "ff_2d/et/_anyb" ]; then
            mkdir -p ff_2d/et/_anyb;
        fi
    else
        mkdir -p ff_2d/et/incl;
        mkdir -p ff_2d/et/_0jet;
        mkdir -p ff_2d/et/_1jet;
        mkdir -p ff_2d/et/_1jetZ050;
        mkdir -p ff_2d/et/_1jetZ50100;
        mkdir -p ff_2d/et/_1jetZ100;
        mkdir -p ff_2d/et/_2jet;
        mkdir -p ff_2d/et/_2jetVBF;
        mkdir -p ff_2d/et/_anyb;
    fi
    if [ ! -d "ff_2d/tt" ]; then
        if [ ! -d "ff_2d/tt/incl" ]; then
            mkdir -p ff_2d/tt/incl;
        fi
        if [ ! -d "ff_2d/tt/_0jet" ]; then
            mkdir -p ff_2d/tt/_0jet;
        fi
        if [ ! -d "ff_2d/tt/_1jet" ]; then
            mkdir -p ff_2d/tt/_1jet;
        fi
        if [ ! -d "ff_2d/tt/_1jetZ050" ]; then
            mkdir -p ff_2d/tt/_1jetZ050;
        fi
        if [ ! -d "ff_2d/tt/_1jetZ50100" ]; then
            mkdir -p ff_2d/tt/_1jetZ50100;
        fi
        if [ ! -d "ff_2d/tt/_1jetZ100" ]; then
            mkdir -p ff_2d/tt/_1jetZ100;
        fi
        if [ ! -d "ff_2d/tt/_2jet" ]; then
            mkdir -p ff_2d/tt/_2jet;
        fi
        if [ ! -d "ff_2d/tt/_2jetVBF" ]; then
            mkdir -p ff_2d/tt/_2jetVBF;
        fi
        if [ ! -d "ff_2d/tt/_anyb" ]; then
            mkdir -p ff_2d/tt/_anyb;
        fi
    else
        mkdir -p ff_2d/tt/incl;
        mkdir -p ff_2d/tt/_0jet;
        mkdir -p ff_2d/tt/_1jet;
        mkdir -p ff_2d/tt/_1jetZ050;
        mkdir -p ff_2d/tt/_1jetZ50100;
        mkdir -p ff_2d/tt/_1jetZ100;
        mkdir -p ff_2d/tt/_2jet;
        mkdir -p ff_2d/tt/_2jetVBF;
        mkdir -p ff_2d/tt/_anyb;
    fi
    
    
else
    mkdir -p ff_2d/mt/incl;
    mkdir -p ff_2d/mt/_0jet;
    mkdir -p ff_2d/mt/_1jet;
    mkdir -p ff_2d/mt/_1jetZ050;
    mkdir -p ff_2d/mt/_1jetZ50100;
    mkdir -p ff_2d/mt/_1jetZ100;
    mkdir -p ff_2d/mt/_2jet;
    mkdir -p ff_2d/mt/_2jetVBF;
    mkdir -p ff_2d/mt/_anyb;
    mkdir -p ff_2d/et/incl;
    mkdir -p ff_2d/et/_0jet;
    mkdir -p ff_2d/et/_1jet;
    mkdir -p ff_2d/et/_1jetZ050;
    mkdir -p ff_2d/et/_1jetZ50100;
    mkdir -p ff_2d/et/_1jetZ100;
    mkdir -p ff_2d/et/_2jet;
    mkdir -p ff_2d/et/_2jetVBF;
    mkdir -p ff_2d/et/_anyb;
    mkdir -p ff_2d/tt/incl;
    mkdir -p ff_2d/tt/_0jet;
    mkdir -p ff_2d/tt/_1jet;
    mkdir -p ff_2d/tt/_1jetZ050;
    mkdir -p ff_2d/tt/_1jetZ50100;
    mkdir -p ff_2d/tt/_1jetZ100;
    mkdir -p ff_2d/tt/_2jet;
    mkdir -p ff_2d/tt/_2jetVBF;
    mkdir -p ff_2d/tt/_anyb;
    
fi




echo $line
