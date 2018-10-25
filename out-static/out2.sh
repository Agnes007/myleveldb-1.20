Keys:       16 bytes each
Values:     1000 bytes each (500 bytes after compression)
Entries:    100000
RawSize:    96.9 MB (estimated)
FileSize:   49.2 MB (estimated)
WARNING: Optimization is disabled: benchmarks unnecessarily slow
WARNING: Assertions are enabled; benchmarks unnecessarily slow
------------------------------------------------
Connected to the cluster.
Ceph shutdown
Connected to the cluster.
fillseq      :   13899.578 micros/op;    0.1 MB/s
Ceph shutdown
Connected to the cluster.
fillsync     :   72259.460 micros/op;    0.0 MB/s (100 ops)
Ceph shutdown
Connected to the cluster.
fillrandom   :   55357.858 micros/op;    0.0 MB/s
overwrite    :   59531.039 micros/op;    0.0 MB/s
readrandom   :   16387.640 micros/op; (100000 of 100000 found)
readrandom   :    2483.644 micros/op; (100000 of 100000 found)
readseq      :       0.886 micros/op; 1094.0 MB/s
readreverse  :       4.151 micros/op;  233.4 MB/s
readrandom   :    1828.650 micros/op; (100000 of 100000 found)
readseq      :       0.964 micros/op; 1004.7 MB/s
readreverse  :       5.846 micros/op;  165.7 MB/s
Ceph shutdown
Connected to the cluster.
fill100K     :   24839.810 micros/op;    3.8 MB/s (100 ops)
acquireload  :       6.412 micros/op; (each op is 1000 loads)
Ceph shutdown
