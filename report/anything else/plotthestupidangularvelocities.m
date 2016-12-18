z = [1500 1139.24 1113.48 1130.03 1102.901600 1151.39 1129.61 1143.54 1116.731700 1160.50 1138.51 1154.01 1126.781800 1167.73 1145.84 1162.39 1134.641900 1173.69 1151.70 1168.14 1141.132000 1178.41 1156.63 1173.07 1146.362100 1182.28 1160.71 1177.57 1150.762200 1185.74 1164.48 1181.34 1154.842300 1200.92 1181.48 1198.10 1172.232400 1201.03 1181.48 1198.20 1172.23];x = z(:,[1]);m1 = z(:,[2]);m2 = z(:,[3]);m3 = z(:,[4]);m4 = z(:,[5]);m1l = [1139.24 1151.39 1160.5 1167.73 1173.69 1178.41];m2l = [1113.48 1129.61 1138.51 1145.84 1151.7 1156.63];m3l = [1130.03 1143.54 1154.01 1162.39 1168.14 1173.07];m4l = [1102.9 1116.73 1126.78 1134.64 1141.13 1146.36];xl = [1500 1600 1700 1800 1900 2000];m1p = polyfit(xl,m1l,2)figureplot(x,m1,x,m2,x,m3,x,m4)title('Angular Velocity vs. Signal');xlabel('Signal (�s)');ylabel('Angular Velocity (rad/s)');legend('Motor 1 ?', 'Motor 2 ?', 'Motor 3 ?', 'Motor 4 ?');grid on