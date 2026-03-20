import os
import xml.etree.ElementTree as ET
from xml.dom import minidom

def prettify(elem):
    rough_string = ET.tostring(elem, 'utf-8')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="    ")

def create_base_fw():
    settings = ET.Element("settings")
    writer = ET.SubElement(settings, "writer")
    writer.text = "writercsv"
    
    filename = ET.SubElement(settings, "filename")
    filename.text = "output"
    
    sims = ET.SubElement(settings, "simulationsperfile")
    sims.text = "1"
    
    case = ET.SubElement(settings, "case")
    rng = ET.SubElement(case, "RNGSettings")
    rng_alg = ET.SubElement(rng, "RNG")
    rng_alg.text = "RandomGeneratorStdLib"
    pool = ET.SubElement(rng, "poolSize")
    pool.text = "100000"
    
    agents = ET.SubElement(case, "agents")
    fw = ET.SubElement(agents, "AgentFW")
    count = ET.SubElement(fw, "count")
    count.text = "1"
    
    fund = ET.SubElement(fw, "AgentFundamentalist")
    ET.SubElement(fund, "phi").text = "0.12"
    ET.SubElement(fund, "sigma").text = "0.758"
    ET.SubElement(fund, "fundamentalPrice").text = "1"
    
    chart = ET.SubElement(fw, "AgentChartist")
    ET.SubElement(chart, "chi").text = "1.5"
    ET.SubElement(chart, "sigma").text = "2.087"
    
    ET.SubElement(fw, "eta").text = "0.991"
    ET.SubElement(fw, "switchingStrategy").text = "DCA"
    ET.SubElement(fw, "beta").text = "1"
    ET.SubElement(fw, "indexStrategy").text = "HPM"
    ET.SubElement(fw, "alpha_0").text = "-0.327"
    ET.SubElement(fw, "alpha_n").text = "1.79"
    ET.SubElement(fw, "alpha_p").text = "18.43"
    ET.SubElement(fw, "delta_n").text = "0.0"
    
    data = ET.SubElement(case, "dataItemCollectorClasses")
    ET.SubElement(data, "DataCollectorPrice")
    ET.SubElement(data, "DataCollectorExcessDemand")
    ET.SubElement(data, "DataCollectorFWShares")
    
    qoi = ET.SubElement(case, "qoi")
    price_qoi = ET.SubElement(qoi, "price")
    ET.SubElement(price_qoi, "full")
    logret_qoi = ET.SubElement(qoi, "logreturn")
    ET.SubElement(logret_qoi, "full")
    ET.SubElement(logret_qoi, "skew")
    ET.SubElement(logret_qoi, "excessKurtosis")

    ET.SubElement(case, "numsteps").text = "2000"
    ET.SubElement(case, "outputname").text = "FW_Sim"
    ET.SubElement(case, "deltaT").text = "1"
    ET.SubElement(case, "writerClass").text = "WriterCSV"
    
    ed = ET.SubElement(case, "excessDemandCalculatorSettings")
    ET.SubElement(ed, "excessDemandCalculatorClass").text = "ExcessDemandCalculatorFW"
    
    pc = ET.SubElement(case, "priceCalculatorSettings")
    ET.SubElement(pc, "priceCalculatorClass").text = "PriceCalculatorFW"
    ET.SubElement(pc, "mu").text = "0.01"
    
    ET.SubElement(case, "stockExchangeClass").text = "StockExchangeHarras"
    ET.SubElement(case, "repetitions").text = "1"
    ET.SubElement(case, "startPrice").text = "1"
    
    return settings

# Helper function
def write_xml(root, path):
    with open(path, "w") as f:
        # PRISM XMLs sometimes complain about XML declaration, but it should be fine
        f.write(prettify(root))

# Ex 1A
root = create_base_fw()
root.find(".//filename").text = "Exp1A_Momentum"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "-0.5" # 100% chartists
fw.find("eta").text = "0"
fw.find("beta").text = "0"
fw.find("AgentChartist/chi").text = "1.5"
fw.find("AgentChartist/sigma").text = "0.1"
write_xml(root, "configs/Exp1A_Momentum.xml")

# Ex 1B
root = create_base_fw()
root.find(".//filename").text = "Exp1B_Random"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "-0.5" # 100% chartists
fw.find("eta").text = "0"
fw.find("beta").text = "0"
fw.find("AgentChartist/chi").text = "0.0" # Pure noise
fw.find("AgentChartist/sigma").text = "2.0"
write_xml(root, "configs/Exp1B_Random.xml")

# Ex 2A
root = create_base_fw()
root.find(".//filename").text = "Exp2A_MeanReversion"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "0.5" # 100% Fundamentalists
fw.find("eta").text = "0"
fw.find("beta").text = "0"
fw.find("AgentFundamentalist/phi").text = "0.5"
fw.find("AgentFundamentalist/sigma").text = "0.1"
write_xml(root, "configs/Exp2A_MeanReversion.xml")

# Ex 2B is Exp1A

# Ex 3A
root = create_base_fw()
root.find(".//filename").text = "Exp3A_PureMix"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "0.0" # 50/50
fw.find("eta").text = "0" # No switching
fw.find("beta").text = "0"
write_xml(root, "configs/Exp3A_PureMix.xml")

# Ex 3B
root = create_base_fw()
root.find(".//filename").text = "Exp3B_MixedSwitching"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "0.0" # 50/50 initial
fw.find("eta").text = "0.991" # Switching on
fw.find("beta").text = "1.0"
write_xml(root, "configs/Exp3B_MixedSwitching.xml")


def create_base_lls():
    settings = ET.Element("settings")
    ET.SubElement(settings, "writer").text = "writercsv"
    ET.SubElement(settings, "filename").text = "output"
    
    case = ET.SubElement(settings, "case")
    rng = ET.SubElement(case, "RNGSettings")
    ET.SubElement(rng, "RNG").text = "RandomGeneratorStdLib"
    
    agents = ET.SubElement(case, "agents")
    lls = ET.SubElement(agents, "AgentLLS")
    ET.SubElement(lls, "cash").text = "1000"
    ET.SubElement(lls, "stock").text = "100"
    ET.SubElement(lls, "riskTolerance").text = "1"
    ET.SubElement(lls, "stdNoiseSigma").text = "0.2"
    ET.SubElement(lls, "initialGamma").text = "0.4"
    emb = ET.SubElement(lls, "AgentEMB")
    ET.SubElement(emb, "count").text = "20"
    ET.SubElement(emb, "memorySpan").text = "15"
    ET.SubElement(emb, "historyMean").text = "0.0415"
    ET.SubElement(emb, "historySigma").text = "0.003"
    
    div = ET.SubElement(case, "dividendSettings")
    ET.SubElement(div, "Z1").text = "0.0149"
    ET.SubElement(div, "Z2").text = "0.0151"
    ET.SubElement(div, "interestRate").text = "0.01"
    ET.SubElement(div, "initialDividend").text = "0.004"
    
    qoi = ET.SubElement(case, "qoi")
    p_qoi = ET.SubElement(qoi, "price")
    ET.SubElement(p_qoi, "full")
    lr_qoi = ET.SubElement(qoi, "logreturn")
    ET.SubElement(lr_qoi, "full")
    
    ET.SubElement(case, "numsteps").text = "1000"
    ET.SubElement(case, "outputname").text = "LLS_Sim"
    ET.SubElement(case, "deltaT").text = "1"
    ET.SubElement(case, "writerClass").text = "WriterCSV"
    
    ed = ET.SubElement(case, "excessDemandCalculatorSettings")
    ET.SubElement(ed, "excessDemandCalculatorClass").text = "ExcessDemandCalculatorLLS"
    
    pc = ET.SubElement(case, "priceCalculatorSettings")
    ET.SubElement(pc, "priceCalculatorClass").text = "PriceCalculatorBisection"
    ET.SubElement(pc, "epsilon").text = "0.01"
    ET.SubElement(pc, "maxIterations").text = "10000"
    ET.SubElement(pc, "lowerBound").text = "0.000001"
    ET.SubElement(pc, "upperBound").text = "20000"
    
    ET.SubElement(case, "repetitions").text = "1"
    ET.SubElement(case, "startPrice").text = "4"
    return settings

# Ex 4A
root = create_base_lls()
root.find(".//filename").text = "Exp4A_ShortMemory"
root.find(".//AgentEMB/memorySpan").text = "5"
write_xml(root, "configs/Exp4A_ShortMemory.xml")

# Ex 4B
root = create_base_lls()
root.find(".//filename").text = "Exp4B_LongMemory"
root.find(".//AgentEMB/memorySpan").text = "50"
write_xml(root, "configs/Exp4B_LongMemory.xml")

# Ex 5A
root = create_base_lls()
root.find(".//filename").text = "Exp5A_NoVolFeedback"
root.find(".//AgentLLS/riskTolerance").text = "1000000" # Ignores risk
write_xml(root, "configs/Exp5A_NoVolFeedback.xml")

# Ex 5B
root = create_base_lls()
root.find(".//filename").text = "Exp5B_VolFeedback"
root.find(".//AgentLLS/riskTolerance").text = "0.1" # Highly sensitive to risk
write_xml(root, "configs/Exp5B_VolFeedback.xml")


def create_base_cross(wealth_constrained=False):
    settings = ET.Element("settings")
    ET.SubElement(settings, "writer").text = "writercsv"
    ET.SubElement(settings, "filename").text = "output"
    
    case = ET.SubElement(settings, "case")
    rng = ET.SubElement(case, "RNGSettings")
    ET.SubElement(rng, "RNG").text = "RandomGeneratorStdLib"
    
    agents = ET.SubElement(case, "agents")
    cross = ET.SubElement(agents, "AgentCrossWealth" if wealth_constrained else "AgentCross")
    ET.SubElement(cross, "count").text = "1000"
    ET.SubElement(cross, "b1").text = "30"
    ET.SubElement(cross, "b2").text = "60"
    ET.SubElement(cross, "A1").text = "0.1"
    ET.SubElement(cross, "A2").text = "0.3"
    ET.SubElement(cross, "cash").text = "1"
    ET.SubElement(cross, "stock").text = "1"
    if wealth_constrained:
        ET.SubElement(cross, "gamma").text = "0.5"
    
    qoi = ET.SubElement(case, "qoi")
    p_qoi = ET.SubElement(qoi, "price")
    ET.SubElement(p_qoi, "full")
    lr_qoi = ET.SubElement(qoi, "logreturn")
    ET.SubElement(lr_qoi, "full")
    
    ET.SubElement(case, "numsteps").text = "1000"
    ET.SubElement(case, "outputname").text = "Cross_Sim"
    ET.SubElement(case, "deltaT").text = "1"
    ET.SubElement(case, "writerClass").text = "WriterCSV"
    
    ed = ET.SubElement(case, "excessDemandCalculatorSettings")
    ET.SubElement(ed, "excessDemandCalculatorClass").text = "ExcessDemandCalculatorHarras"
    
    pc = ET.SubElement(case, "priceCalculatorSettings")
    ET.SubElement(pc, "priceCalculatorClass").text = "PriceCalculatorCross"
    ET.SubElement(pc, "theta").text = "0.01"
    ET.SubElement(pc, "marketDepth").text = "2"
    
    div = ET.SubElement(case, "dividendSettings")
    ET.SubElement(div, "Z1").text = "0.005"
    ET.SubElement(div, "Z2").text = "0.015"
    ET.SubElement(div, "interestRate").text = "0.01"
    ET.SubElement(div, "initialDividend").text = "0.01"

    ET.SubElement(case, "stockExchangeClass").text = "StockExchangeHarras"
    ET.SubElement(case, "repetitions").text = "1"
    ET.SubElement(case, "startPrice").text = "1"
    return settings

# Ex 6A
root = create_base_cross(False)
root.find(".//filename").text = "Exp6A_Symmetric"
write_xml(root, "configs/Exp6A_Symmetric.xml")

# Ex 6B
root = create_base_cross(True)
root.find(".//filename").text = "Exp6B_Asymmetric"
write_xml(root, "configs/Exp6B_Asymmetric.xml")


def create_base_harras():
    settings = ET.Element("settings")
    ET.SubElement(settings, "writer").text = "writercsv"
    ET.SubElement(settings, "filename").text = "output"
    
    case = ET.SubElement(settings, "case")
    rng = ET.SubElement(case, "RNGSettings")
    ET.SubElement(rng, "RNG").text = "RandomGeneratorStdLib"
    
    agents = ET.SubElement(case, "agents")
    har = ET.SubElement(agents, "AgentHarras")
    ET.SubElement(har, "count").text = "250"
    ET.SubElement(har, "C1").text = "0"
    ET.SubElement(har, "C2").text = "1"
    ET.SubElement(har, "C3").text = "1"
    ET.SubElement(har, "threshold").text = "2"
    ET.SubElement(har, "g").text = "0.02"
    ET.SubElement(har, "alpha").text = "0.95"
    ET.SubElement(har, "neighbourhoodGeneratorClass").text = "LatticeNeighbourhoodGenerator"
    ET.SubElement(har, "cash").text = "1"
    ET.SubElement(har, "stock").text = "1"
    
    qoi = ET.SubElement(case, "qoi")
    p_qoi = ET.SubElement(qoi, "price")
    ET.SubElement(p_qoi, "full")
    lr_qoi = ET.SubElement(qoi, "logreturn")
    ET.SubElement(lr_qoi, "full")
    
    ET.SubElement(case, "numsteps").text = "1000"
    ET.SubElement(case, "outputname").text = "Harras_Sim"
    ET.SubElement(case, "deltaT").text = "1"
    ET.SubElement(case, "writerClass").text = "WriterCSV"
    
    ed = ET.SubElement(case, "excessDemandCalculatorSettings")
    ET.SubElement(ed, "excessDemandCalculatorClass").text = "ExcessDemandCalculatorHarras"
    
    pc = ET.SubElement(case, "priceCalculatorSettings")
    ET.SubElement(pc, "priceCalculatorClass").text = "PriceCalculatorHarras"
    ET.SubElement(pc, "marketDepth").text = "2"
    
    ET.SubElement(case, "stockExchangeClass").text = "StockExchangeHarras"
    ET.SubElement(case, "repetitions").text = "1"
    ET.SubElement(case, "startPrice").text = "1"
    return settings

# Ex 7A
root = create_base_harras()
root.find(".//filename").text = "Exp7A_Small"
root.find(".//AgentHarras/count").text = "100"
write_xml(root, "configs/Exp7A_Small.xml")

# Ex 7B
root = create_base_harras()
root.find(".//filename").text = "Exp7B_Medium"
root.find(".//AgentHarras/count").text = "1024" # 32^2
write_xml(root, "configs/Exp7B_Medium.xml")

# Ex 7C
root = create_base_harras()
root.find(".//filename").text = "Exp7C_Large"
root.find(".//AgentHarras/count").text = "10000"
write_xml(root, "configs/Exp7C_Large.xml")

# Ex 8A
root = create_base_fw()
root.find(".//filename").text = "Exp8A_Short"
root.find(".//numsteps").text = "500"
write_xml(root, "configs/Exp8A_Short.xml")

# Ex 8B
root = create_base_fw()
root.find(".//filename").text = "Exp8B_Medium"
root.find(".//numsteps").text = "5000"
write_xml(root, "configs/Exp8B_Medium.xml")

# Ex 8C
root = create_base_fw()
root.find(".//filename").text = "Exp8C_Long"
root.find(".//numsteps").text = "20000"
write_xml(root, "configs/Exp8C_Long.xml")

# Ex 9A
root = create_base_fw()
root.find(".//filename").text = "Exp9A_Rational"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "0.5" # 100% Fundamentalists
fw.find("eta").text = "0"
fw.find("beta").text = "0"
fw.find("AgentFundamentalist/phi").text = "0.5"
fw.find("AgentFundamentalist/sigma").text = "0.01" # Highly rational, very low noise
write_xml(root, "configs/Exp9A_Rational.xml")

# Ex 9B
root = create_base_fw()
root.find(".//filename").text = "Exp9B_Noisy"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "0.5" # 100% Fundamentalists
fw.find("eta").text = "0"
fw.find("beta").text = "0"
fw.find("AgentFundamentalist/phi").text = "0.5"
fw.find("AgentFundamentalist/sigma").text = "2.0" # High noise
write_xml(root, "configs/Exp9B_Noisy.xml")

# Ex 10 Regime Switching
root = create_base_fw()
root.find(".//filename").text = "Exp10_RegimeSwitching"
fw = root.find(".//AgentFW")
fw.find("delta_n").text = "0.0" # Start 50/50
fw.find("eta").text = "0.991" # High switching rate
fw.find("beta").text = "1"
fw.find("switchingStrategy").text = "TPAC" # Transition Probability with noise
root.find(".//numsteps").text = "10000" # Long enough to see regimes
write_xml(root, "configs/Exp10_RegimeSwitching.xml")
