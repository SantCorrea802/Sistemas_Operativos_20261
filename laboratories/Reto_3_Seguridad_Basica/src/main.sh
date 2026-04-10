#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
APP_COMMAND_PATH="$(readlink -f "${BASH_SOURCE[0]}" 2>/dev/null || realpath "${BASH_SOURCE[0]}")"

# shellcheck source=/dev/null
source "${ROOT_DIR}/include/config/app.conf"
# shellcheck source=/dev/null
source "${SCRIPT_DIR}/utils/validation.sh"
# shellcheck source=/dev/null
source "${SCRIPT_DIR}/user/user.sh"
# shellcheck source=/dev/null
source "${SCRIPT_DIR}/policy/policy.sh"

show_help() {
  cat <<EOF
Uso:
  ./src/main.sh list-users
  ./src/main.sh create <usuario> [clave]
  ./src/main.sh lock <usuario>
  ./src/main.sh unlock <usuario>
  ./src/main.sh delete <usuario>
  ./src/main.sh add-sudo <usuario>
  ./src/main.sh check-expired
  ./src/main.sh install-warning
  ./src/main.sh help
EOF
}

main() {
  require_root

  local command="${1:-help}"
  local username password

  case "${command}" in
    list-users)
      list_system_users
      ;;
    create)
      username="${2:-}"
      password="${3:-${DEFAULT_PASSWORD}}"

      if [[ -z "${username}" ]]; then
        echo "Error: falta usuario." >&2
        show_help
        exit 1
      fi

      validate_password_policy "${password}"
      create_system_user "${username}" "${password}" "${PASSWORD_MAX_DAYS}" "${PASSWORD_WARN_DAYS}"
      ;;
    lock)
      username="${2:-}"
      [[ -n "${username}" ]] || { echo "Error: falta usuario." >&2; exit 1; }
      lock_system_user "${username}"
      ;;
    unlock)
      username="${2:-}"
      [[ -n "${username}" ]] || { echo "Error: falta usuario." >&2; exit 1; }
      unlock_system_user "${username}"
      ;;
    delete)
      username="${2:-}"
      [[ -n "${username}" ]] || { echo "Error: falta usuario." >&2; exit 1; }
      delete_system_user "${username}"
      ;;
    add-sudo)
      username="${2:-}"
      [[ -n "${username}" ]] || { echo "Error: falta usuario." >&2; exit 1; }
      add_user_to_sudoers "${username}" "${APP_COMMAND_PATH}"
      ;;
    check-expired)
      lock_expired_users
      ;;
    install-warning)
      install_warning_login_script "${PASSWORD_WARN_DAYS}" "${CUSTOM_WARNING_MESSAGE}"
      ;;
    help|--help|-h)
      show_help
      ;;
    *)
      echo "Error: comando no valido: ${command}" >&2
      show_help
      exit 1
      ;;
  esac
}

main "$@"
