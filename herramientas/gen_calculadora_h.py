#!/usr/bin/env python3
"""Genera desktop/calculadora_js.h: el botón «TMP Calculadora» (calculadora/tmp-calculadora-flotante.js) embebido en el binario de Linux,
para que funcione igual en RPM, DEB, AppImage, Flatpak y Snap sin depender de rutas de instalación."""
import os
R=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
b=open(os.path.join(R,'calculadora/tmp-calculadora-flotante.js'),'rb').read()+b'\0'
with open(os.path.join(R,'desktop/calculadora_js.h'),'w') as f:
    f.write('/* Generado por herramientas/gen_calculadora_h.py — no editar. */\nstatic const char CALCULADORA_JS[] = {\n')
    for i in range(0,len(b),24): f.write('  '+', '.join('0x%02x'%x for x in b[i:i+24])+',\n')
    f.write('};\n')
print('desktop/calculadora_js.h',len(b)//1024,'KB')
