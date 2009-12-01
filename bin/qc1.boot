#! /bin/sh

swipl -x /home/pjr/research/qp_dev/rel/qp8.10/bin/qc1.boot.po -F none -f none -t halt -g "main(['$1'])"
