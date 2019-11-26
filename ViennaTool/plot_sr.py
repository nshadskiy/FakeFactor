#!/usr/bin/env python
# -*- coding: utf-8 -*-

import HiggsAnalysis.KITHiggsToTauTau.plotting.higgsplot as higgsplot

import argparse
from copy import deepcopy

import logging
logger = logging.getLogger("")


def parse_arguments():
    parser = argparse.ArgumentParser(
        description=
        "Plot categories using HarryPlotter from shapes produced by shape-producer module."
    )
    parser.add_argument("--comparison", action="store_true", help="Plot Embedded - MC comparison. --emb has to be set.")

    parser.add_argument("--emb", action="store_true", help="Embedded prefix")
    parser.add_argument("--ff", action="store_true", help="Use fake-factors")
    parser.add_argument(
        "-v",
        "--variables",
        nargs="+",
        type=str,
        required=True,
        help="Variable on x-axis")
    parser.add_argument(
        "--categories",
        nargs="+",
        type=str,
        required=False, default=None,
        help="Categories")
    parser.add_argument("--era", type=str, default="2016", help="Era")
    parser.add_argument(
        "--lumi", type=float, default=None, help="Integrated Luminosity")
    parser.add_argument(
        "--additional-arguments",
        type=str,
        default="",
        help="Additional higgsplot.py arguments")
    parser.add_argument(
        "--output-dir",
        type=str,
        default="plots",
        help="Output directory for plots")
    parser.add_argument(
        "--y-log",
        action="store_true",
        default=False,
        help="Use logarithmic y-axis")
    parser.add_argument(
        "-c",
        "--channels", nargs="+", type=str, required=True, help="Channel")
    parser.add_argument(
        "--x-label", type=str, default=None, help="Label on x-axis")
    parser.add_argument("--chi2", action="store_true", help="Print chi2 value")
    parser.add_argument(
        "--num-processes",
        type=int,
        default=24,
        help="Number of processes used for plotting")

    parser.add_argument("--filename-prefix", type=str, default="", help="filename prefix")
    parser.add_argument("--www", action="store_true", help="webplotting")
    parser.add_argument("--www-dir", type=str, default=None,
        help='Directory structure where the plots will be uploaded. {date} expressions will be replaced by date.')
    parser.add_argument("--www-no-overwrite", action='store_true', default=False, help="Don't overwrite remote file. [Default: %(default)s]")
    parser.add_argument("--no-overwrite", "--keep-both", "--keep", "-k", action='store_true', default=False, help="Don't overwrite output file. [Default: %(default)s]")
    parser.add_argument("--log-level", default="debug", help="log level. [Default: %(default)s]")
    parser.add_argument("--redo-cache", action="store_true",
                        help="Do not use inputs from cached trees, but overwrite them. [Default: False for absolute paths, True for relative paths]")

    return parser.parse_args()


def setup_logging(output_file, level=logging.DEBUG):
    logger.setLevel(level)
    formatter = logging.Formatter("%(name)s - %(levelname)s - %(message)s")

    handler = logging.StreamHandler()
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    file_handler = logging.FileHandler(output_file, "w")
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)


config_template = {
    "colors": ["#B7B7B7", "#000000"],
    "filename": "",
    "files": [None],
    "labels": ["", ""],
    "legend": [0.4, 0.52, 0.88, 0.83],
    "legend_cols": 2,
    "legend_markers": ["ELP", "ELP"],
    "stacks": ["ratio_bkg", "ratio_data"],
    "markers": ["E2", "P"],
    "formats": ["pdf", "png"],
    "title": "",
    "cms": True,
    "extra_text": "work in progress",
    "energies": [13],
    "nicks_blacklist": ["noplot"],
    "analysis_modules": ["Ratio"],
    "ratio_result_nicks": ["ratio_Bkg", "ratio_Data"],
    "y_subplot_lims": [0.62, 1.5],
    "y_label": "N_{evts}",
    "y_subplot_label": "#scale[0.8]{stat bkg unc.}",
    "subplot_lines": [0.8, 1.0, 1.2]
}

logvars = ["nbtag","njets","jpt_1","jpt_2"]


def main(args):

    if args.emb:
        bkg_processes_names = ["emb", "zll","zj", "ttl", "ttj","vvl", "vvj", "w"]
        bkg_processes = ["EMB", "DY_L", "DY_J","TT_L", "TT_J","VV_L", "VV_J", "Wjets"]
    else:
        bkg_processes_names = [
            "ztt", "zll","zj","ttt", "ttl","ttj","vvt","vvl","vvj","w"]
        bkg_processes = ["DY_TT","DY_L", "DY_J", "TT_T", "TT_L", "TT_J", "VV_T", "VV_L","VV_J","Wjets"]
    channels = args.channels
    era = args.era
    if args.lumi is None:
        if "2016" in era:
            lumi = 35.9
        elif "2017" in era:
            lumi = 41.5
        elif "2018" in era:
            lumi = 59.7
    else:
        lumi=args.lumi
    output_dir = args.output_dir
    y_log = args.y_log
    variables = args.variables
    categories = ["SR"]
    variables = args.variables#["mvis","mt","muiso","pt","lepPt"]
    working_points = ["tight","loose"] 
    if args.www:
        config_template['www'] = ''
    if args.www_dir:
        config_template['www_dir'] = args.www_dir
    if args.www_no_overwrite:
        config_template['www_no_overwrite'] = True
        config_template['no_overwrite'] = True
    if args.no_overwrite:
        config_template['no_overwrite'] = True
    if args.redo_cache:
        config_template['redo_cache'] = True

    if args.filename_prefix != '':
        args.filename_prefix = args.filename_prefix if args.filename_prefix[0] == '_' else '_' + args.filename_prefix
    # if args.log_level == 'debug':
        # config['log_level'] =

    configs = []
    for y_log in [True,False]:
        for channel in channels:
            for category in categories:
                for variable in variables:
                    for wp in working_points:
                        config = deepcopy(config_template)
                        config["files"] = []
                        if args.chi2:
                            config["analysis_modules"].append("AddHistograms")
                            config["analysis_modules"].append("Chi2Test")
                            config["add_nicks"] = [" ".join(bkg_processes_names)]
                            config["add_result_nicks"] = ["tot_background_noplot"]
                            config["chi2test_nicks"] = ["tot_background_noplot data"]
                            config["chi2test_compare"] = ["UU CHI2/NDF"]
                        for bkg_process in bkg_processes + ["data"]:
                            config["files"].append("sim/{}/SR_{}_{}.root".format(channel,bkg_process,variable))
                            # else:
                            #     config["files"].append("sim/{}/SR_{}_{}_data_MCsubtracted.root".format(channel,category,variable))                                
                        config["lumis"] = [lumi]
                        config["year"] = era.strip("Run")
                        config["output_dir"] = output_dir+"/"+channel
                        config["y_log"] = True if ((variable in logvars) or y_log) else False
                        config["y_rel_lims"] = [5, 500] if (variable in logvars or y_log) else [0.9, 1.5]
                        config["markers"] = ["HIST"] * len(bkg_processes_names) + ["P"] + ["E2"] + ["P"]
                        config["legend_markers"] = ["F"] * (len(bkg_processes_names))  +  ["ELP"] + ["E2"] + ["P"]
                        config["labels"] = bkg_processes_names + ["data"
                                                                ] + config["labels"]
                        config["colors"] = bkg_processes_names + ["data"
                                                                ] + ["#B7B7B7"] + ["#000000"]
                        config["nicks"] = bkg_processes_names + ["data"]
                        config["x_expressions"] = ["hh_{}_{}".format(wp[0],variable.replace("_AI",""))]
                        if args.emb == False:
                            config["filename"] = "_".join(
                                [channel, category, wp, era, variable]) + args.filename_prefix
                        else:
                            config["filename"] = "_".join(
                                [channel, category, wp, era, variable,"emb"]) + args.filename_prefix
                        if y_log:
                            config["filename"] += "_log"
                        if args.ff:
                            config["filename"] = config["filename"]+"_ff"
                        if not args.x_label == None:
                            config["x_label"] = args.x_label
                        else:
                            config["x_label"] = "_".join([channel, variable])
                        config["title"] = "{} {} {}".format(channel,category,wp)#"_".join(["channel", channel])
                        config["stacks"] = ["mc"] * len(bkg_processes_names) + ["data","ratio_A","ratio_B"]
                        config["ratio_denominator_nicks"] = [" ".join(bkg_processes_names)] * 2
                        config["ratio_numerator_nicks"] = [" ".join(bkg_processes_names)] + ["data"]
                        config["ratio_result_nicks"] = ["bkg_ratio"] + ["data_ratio"]
            
                        configs.append(config)

    higgsplot.HiggsPlotter(
        list_of_config_dicts=configs,
        list_of_args_strings=[args.additional_arguments],
        n_processes=args.num_processes)


if __name__ == "__main__":
    args = parse_arguments()
    if args.log_level == 'debug':
        ll = logging.DEBUG
    else:
        ll = logging.INFO
    setup_logging("plot_nominal.log", ll)
    main(args)
