{
  "targets": [
    {
      "target_name": "devicedisplayops",
      "sources": [
        "src/devicedisplay.cpp",
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
      ],
    }
  ]
}