#!/usr/bin/env bash

add_user_to_sudoers() {
  local username="$1"
  local app_command_path="$2"
  local sudo_file="/etc/sudoers.d/lab_${username}"

  if ! user_exists "${username}"; then
    echo "Error: el usuario ${username} no existe." >&2
    return 1
  fi

  echo "${username} ALL=(root) NOPASSWD: ${app_command_path} *" >"${sudo_file}" || return 1
  chmod 440 "${sudo_file}" || return 1

  visudo -cf "${sudo_file}" >/dev/null || {
    rm -f "${sudo_file}"
    echo "Error: configuracion sudoers invalida." >&2
    return 1
  }

  echo "Usuario ${username} agregado a sudoers para comandos del laboratorio."
}

lock_expired_users() {
  local username expires now_ts exp_ts
  now_ts=$(date +%s)

  while read -r username; do
    expires=$(chage -l "${username}" | awk -F': ' '/Password expires/ {print $2}')

    if [[ "${expires}" == "never" ]]; then
      continue
    fi

    if [[ "${expires}" == "password must be changed" ]]; then
      usermod -L "${username}" >/dev/null 2>&1
      continue
    fi

    exp_ts=$(date -d "${expires}" +%s 2>/dev/null || echo 0)

    if [[ "${exp_ts}" -gt 0 && "${exp_ts}" -lt "${now_ts}" ]]; then
      usermod -L "${username}" >/dev/null 2>&1
      echo "Usuario ${username} bloqueado por clave vencida."
    fi
  done < <(list_system_users)
}

install_warning_login_script() {
  local warning_days="$1"
  local custom_message="$2"
  local target="/etc/profile.d/lab_password_warning.sh"

  cat >"${target}" <<EOF
#!/usr/bin/env bash

if [[ "\${EUID}" == "0" ]] 2>/dev/null; then
  return 0 2>/dev/null || exit 0
fi

exp_date=\$(chage -l "\$USER" | awk -F': ' '/Password expires/ {print \$2}')
if [[ "\${exp_date}" == "never" || "\${exp_date}" == "password must be changed" ]]; then
  return 0 2>/dev/null || exit 0
fi

exp_ts=\$(date -d "\${exp_date}" +%s 2>/dev/null || echo 0)
now_ts=\$(date +%s)
if [[ "\${exp_ts}" -le 0 ]]; then
  return 0 2>/dev/null || exit 0
fi

days_left=\$(( (exp_ts - now_ts) / 86400 ))
if [[ "\${days_left}" -le ${warning_days} && "\${days_left}" -ge 0 ]]; then
  echo "${custom_message}"
  echo "Dias restantes: \${days_left}."
fi
EOF

  chmod +x "${target}" || return 1
  echo "Script de advertencia instalado en ${target}."
}
