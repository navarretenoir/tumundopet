#!/usr/bin/env bash
# Tu Mundo Pet carga la tienda en línea; solo se copia el botón «TMP Calculadora» (calculadora/tmp-calculadora-flotante.js) como recurso.
set -euo pipefail
A=$(cd "$(dirname "$0")" && pwd); W="$A/Recursos/web"
mkdir -p "$W"; cp "$A/../calculadora/tmp-calculadora-flotante.js" "$W/"
echo "✔ Recursos/web listo (tmp-calculadora-flotante.js)"
