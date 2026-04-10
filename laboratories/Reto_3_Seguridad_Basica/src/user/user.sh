#!/usr/bin/env bash

list_system_users() {
  awk -F: '$3 >= 1000 && $1 != "nobody" { print $1 }' /etc/passwd
}

create_system_user() {
  local username="$1"
  local password="$2"
  local max_days="$3"
  local warn_days="$4"

  if user_exists "${username}"; then
    echo "Error: el usuario ${username} ya existe." >&2
    return 1
  fi

  useradd -m -s /bin/bash "${username}" || return 1
  echo "${username}:${password}" | chpasswd || return 1

  # Force change on first login and set password aging policy.
  passwd -e "${username}" >/dev/null 2>&1 || return 1
  chage -M "${max_days}" -W "${warn_days}" -I 0 "${username}" || return 1

  echo "Usuario ${username} creado correctamente."
}

lock_system_user() {
  local username="$1"

  if ! user_exists "${username}"; then
    echo "Error: el usuario ${username} no existe." >&2
    return 1
  fi

  usermod -L "${username}" || return 1
  echo "Usuario ${username} bloqueado."
}

unlock_system_user() {
  local username="$1"

  if ! user_exists "${username}"; then
    echo "Error: el usuario ${username} no existe." >&2
    return 1
  fi

  usermod -U "${username}" || return 1
  echo "Usuario ${username} activado."
}

delete_system_user() {
  local username="$1"

  if ! user_exists "${username}"; then
    echo "Error: el usuario ${username} no existe." >&2
    return 1
  fi

  userdel -r "${username}" || return 1
  rm -f "/etc/sudoers.d/lab_${username}"
  echo "Usuario ${username} eliminado."
}
