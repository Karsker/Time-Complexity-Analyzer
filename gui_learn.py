import tkinter as tk
from tkinter import filedialog
import os
from os import listdir
from subprocess import run
#import xlwt
#from xlwt import Workbook
import random
import string
#import grapher
#from grapher import generateGraphs
import excelOps
from excelOps import writeRunTimesToSheet
# Global variables
fileToRun = '' #  Stores the paths of C++ files
runTimes = [] # Stores the run times of the C++ programs
inputSizes = [] # Stores the input sizes for which the time is calculated
sheetRow = 1 # only for spreadsheet output, can be ignored for now
sheetCol = 1
graphRow = 20
spreadSheetPath = ''

main_window = tk.Tk(className='Graph Generator')
main_window.geometry("1280x720")



# Function that will handle the execution of C++ files

def clearRandomFiles():
    folderPath = './'
    for fileName in listdir(folderPath):
        if fileName.startswith('random_'):
            os.remove(folderPath+fileName)

def genGraphs():
    global sheetCol, graphRow
    writeRunTimesToSheet(spreadSheetPath, inputSizes, runTimes, sheetRow, sheetCol, fileToRun, graphRow)
    header.configure(text="Graph Successfully generated in the Excel file selected.")
    runTimeOutput.delete(1.0, "end")
    sheetCol += 3
    graphRow += 18

def runCodeFile():
    global runTimes, runTimeOutput, header
    header.configure(text='Running...')
    runTimeOutput.delete(1.0, "end")
    if sheetCol > 1:
        runTimes = []
    #print(inputSizes)
    os.system('g++ ' + '"' + fileToRun + '"' + ' -o daaOut.exe')
    for j in range(0, len(inputSizes)):
        cmd = 'powershell.exe Get-Content random_' + inputSizes[j] + '.txt | ./daaOut.exe' 
        currRunTime = run(cmd, capture_output=True, shell=True).stdout
        print(currRunTime)
        runTimes.append(float(currRunTime.decode().split('\n')[0]))
    header.configure(text="Check runtimes before generating graph.")
    #print("Run times for " + os.path.basename(fileToRun))
    runTimeOutput.insert(tk.END, runTimes[0])
    for j in range(1, len(runTimes)):
        #print(j)
        runTimeOutput.insert(tk.END, ', ' + str(runTimes[j]))
    print("")
    
    

def reRun():
    global runTimes
    runTimes = []
    runCodeFile()
# Function to generate 'm' random alphabets
def generateAlphabets(m):
    n = int(m)
    fp = open("random_" + str(n) + ".txt","w")
    fp.write(str(n)+" ")  
    for i in range(1,n):
        randomLetter = random.choice(string.ascii_letters)
        fp.write(randomLetter+" ")  
    randomLetter = random.choice(string.ascii_letters)
    fp.write(randomLetter)
    fp.close()

# Function to generate 'm' random positive integers
def generatePosNumbers(m):
    n = int(m)
    fp = open("random_" + str(n) + ".txt","w")
    fp.write(str(n)+" ")  
    for i in range(1,n):
        x = random.random()
        fp.write(str(int(x*n))+" ")  
    x = random.random()
    fp.write(str(int(x*n))+" ")
    fp.close()

# Function to generate numbers that contain both positive and negetive integers
def generateNegNumbers(m):
    n = int(m)
    fp = open("random_" + str(n) + ".txt","w")
    fp.write(str(n)+" ")  
    for i in range(1,n):
        x = random.random()
        if (i%2 == 0):
            fp.write(str(-int(x*n))+" ")
        else:
            fp.write(str(int(x*n))+" ")
    x = random.random()
    fp.write(str(int(x*n))+" ")
    fp.close()

# Function that generates random numbers based on input size from the user
def confInputSizes(size):
    inpType = inputType.get()
    #size = randomCnt.get()
    if inpType == 1:
        generateAlphabets(size)
    elif inpType == 2:
        generatePosNumbers(size)
    else:
        generateNegNumbers(size)
    #inputSizes.append(size)
    header.configure(text='Added ' + str(size) + ' to input sizes')


# Function to handle file browsing 
def browser():
        global fileToRun
        fileToRun = filedialog.askopenfilename(initialdir = "C:",
                                          title = "Select a File",
                                          filetypes = (("C++ files",
                                                        "*.cpp*"),
                                                       ("all files",
                                                        "*.*")), parent=main_window)
      
        if fileToRun == '':
            header.configure(text='No file selected')
        else:
            header.configure(text=os.path.basename(fileToRun) + ' ready to run.')

#Function to select spreadsheet file (Excel file)
def selectSpreadsheet():
    global spreadSheetPath 
    spreadSheetPath = filedialog.askopenfilename(initialdir = "C:",
                                          title = "Select a File",
                                          filetypes = (("Excel files",
                                                        "*.xlsx*"),
                                                       ("all files",
                                                        "*.*")), parent=main_window)
    if spreadSheetPath == '':
        header.configure(text='No file selected')
    #print(spreadSheetPath)
    
# Function to select input sizes file
def selectInputSizes():
        filename = filedialog.askopenfilename(initialdir = "C:",
                                          title = "Select a File",
                                          filetypes = (("Text files",
                                                        "*.txt*"),
                                                       ("all files",
                                                        "*.*")), parent=main_window)
      
        global inputSizes
        f = open(filename, "r")
        inputSizes = f.read().splitlines()
        # print(inputSizes)
        for size in inputSizes:
            confInputSizes(size)
main_window.grid_rowconfigure(0,weight=1)
main_window.grid_columnconfigure(0, weight=1)

textFrame = tk.Frame(main_window)
textFrame.grid(row=0)
header = tk.Label(textFrame, text='Welcome to DAA Graph Generator', font = ('Arial', 16))
header.grid(row=0)
runTimeOutput = tk.Text(textFrame, height=5, width=49)
runTimeOutput.grid(row=1)

def resetGraphs():
    global sheetCol, sheetRow
    sheetCol = 1
    sheetRow = 1
# Button to configure CPP files to run
codeConfButton = tk.Button(main_window, text='Select CPP File', font=('Arial', 10), borderwidth=2, command=browser)
codeConfButton.grid(row = 2, pady=10, ipadx=5, ipady=5)

# Button to configure excel file
sheetConfButton = tk.Button(main_window, text='Select spreadsheet File', font=('Arial', 10), borderwidth=2, command=selectSpreadsheet)
sheetConfButton.grid(row = 3, pady=10, ipadx=5, ipady=5)

#Button to close the window
tk.Button(main_window, bg="blue", text='Close',fg='white' ,command=lambda: [clearRandomFiles(), main_window.destroy()]).grid(row=7, pady=10)


#Radio buttons to give options
radioFrame = tk.Frame(main_window)
radioFrame.grid(row=6, pady=10)
inputType = tk.IntVar()
alphabetRadio = tk.Radiobutton(radioFrame, text='Generate alphabets', font=('Arial', 12), variable=inputType, value=1,)
alphabetRadio.grid(row=0, column=0, padx=5)
posNumbersRadio = tk.Radiobutton(radioFrame, text='Generate Positive Numbers', font=('Arial', 12), variable=inputType, value=2)
posNumbersRadio.grid(row=0,column=1, padx=5)
negNumbersRadio = tk.Radiobutton(radioFrame, text='Generate Negetive Numbers', font=('Arial', 12), variable=inputType, value=3)
negNumbersRadio.grid(row=0,column=2, padx=5)

# Widgets for handling input sizes
tk.Button(main_window, bg="red", text='Run',fg='white' ,command=runCodeFile).grid(row=8, pady=10)
randomNumFrame = tk.Frame(main_window)
randomNumFrame.grid(row=4)
# tk.Label(randomNumFrame,text='Enter input sizes here: ', font=('Arial', 10)).grid(row=0)
# randomCnt = tk.Entry(randomNumFrame)
# randomCnt.grid(row=1)
genButton = tk.Button(randomNumFrame, text='Choose input file', font=('Arial', 10), borderwidth=2, command=selectInputSizes)
genButton.grid(row = 1, pady=10, ipadx=5, ipady=5)
reRun = tk.Button(randomNumFrame, text='Re Run', font=('Arial', 10), borderwidth=2, command=reRun)
reRun.grid(row=2, pady=10, ipadx=5, ipady=5)
genGraph = tk.Button(randomNumFrame, text='Generate Graph', font=('Arial', 10), borderwidth=2, command = genGraphs)
genGraph.grid(row=3, pady=10, ipadx=5, ipady=5)
resetGraph = tk.Button(randomNumFrame, text='Reset Graph Index', font=('Arial', 10), borderwidth=2, command = resetGraphs)
resetGraph.grid(row=4, pady=10, ipadx=5, ipady=5)
main_window.mainloop()