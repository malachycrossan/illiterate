#set document(title: "Test Results Report", author: "GitHub Actions")
#set page(numbering: "1", margin: 1in)
#set text(font: "Linux Libertine", size: 11pt)

#align(center)[
  #text(size: 20pt, weight: "bold")[Automated Test Results Report]
  
  #v(0.5em)
  
  #text(size: 12pt)[GitHub Actions]
  
  #v(0.5em)
  
  #text(size: 10pt)[2026-02-08 05:41:54 UTC]
]

#v(1em)

= Summary

#table(
  columns: (auto, auto),
  align: left,
  [*Metric*], [*Count*],
  [Commit], [`50685f2`],
  [Total Tests], [1],
  [Passed], [#text(fill: green)[0 ✓]],
  [Failed], [#text(fill: red)[1 ✗]],
  [Success Rate], [0%],
)

#v(1em)

== Overall Status

#text(fill: red, weight: "bold")[Some tests failed.]

#v(1em)

= Detailed Results

#v(0.5em)

== #text(fill: red)[example solution example solution test1 - FAILED]

