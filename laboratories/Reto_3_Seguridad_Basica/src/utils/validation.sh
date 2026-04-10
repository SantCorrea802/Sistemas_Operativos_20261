#!/usr/bin/env bash

require_root() {
  if [[ "${EUID}" -ne 0 ]]; then
    echo "Error: solo root puede ejecutar este laboratorio." >&2
    exit 1
  fi
}

user_exists() {
  id "$1" >/dev/null 2>&1
}

validate_password_policy() {
  local password="$1"

  if [[ -z "${password}" ]]; then
    echo "Error: la clave no puede estar vacia." >&2
    return 1
  fi

  if [[ "${password}" =~ [[:space:]] ]]; then
    echo "Error: la clave no puede tener espacios." >&2
    return 1
  fi

  if ! [[ "${password}" =~ [A-Z] ]]; then
    echo "Error: la clave debe tener al menos una mayuscula." >&2
    return 1
  fi

  if ! [[ "${password}" =~ [^a-zA-Z0-9] ]]; then
    echo "Error: la clave debe tener al menos un caracter especial." >&2
    return 1
  fi

  return 0
}
