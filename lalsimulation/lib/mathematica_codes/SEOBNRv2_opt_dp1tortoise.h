REAL8 tmp53=sigmaKerr->data[2]*sigmaKerr->data[2];
REAL8 tmp54=sqrt(tmp53);
REAL8 tmp83=coeffs->KK*eta;
REAL8 tmp145=-1.+tmp83;
REAL8 tmp56=1/x->data[0];
REAL8 tmp60=x->data[0]*x->data[0];
REAL8 tmp153=(1.0/(x->data[0]*x->data[0]));
REAL8 tmp5=1.*e3z;
REAL8 tmp48=0.+tmp5;
REAL8 tmp81=tmp53+tmp60;
REAL8 tmp82=tmp81*tmp81;
REAL8 tmp149=(1.0/(tmp145*tmp145));
REAL8 tmp152=1.*tmp149;
REAL8 tmp156=1.*tmp153*tmp53;
REAL8 tmp157=1/tmp145;
REAL8 tmp158=2.*tmp157*tmp56;
REAL8 tmp159=tmp152+tmp156+tmp158;
REAL8 tmp160=coeffs->k0*eta;
REAL8 tmp161=1./(x->data[0]*x->data[0]*x->data[0]*x->data[0]);
REAL8 tmp164=1.*coeffs->k4*tmp161;
REAL8 tmp165=1./(x->data[0]*x->data[0]*x->data[0]);
REAL8 tmp166=1.*coeffs->k3*tmp165;
REAL8 tmp167=1.*coeffs->k2*tmp153;
REAL8 tmp168=1.*coeffs->k1*tmp56;
REAL8 tmp169=pow(x->data[0],-5.);
REAL8 tmp170=1.*tmp56;
REAL8 tmp190=log(tmp170);
REAL8 tmp191=coeffs->k5l*tmp190;
REAL8 tmp192=coeffs->k5+tmp191;
REAL8 tmp193=1.*tmp169*tmp192;
REAL8 tmp196=1.+tmp164+tmp166+tmp167+tmp168+tmp193;
REAL8 tmp198=log(tmp196);
REAL8 tmp201=eta*tmp198;
REAL8 tmp202=1.+tmp160+tmp201;
REAL8 tmp204=-(tmp159*tmp202*tmp53*tmp60);
REAL8 tmp205=tmp204+tmp82;
REAL8 tmp206=1/tmp205;
REAL8 tmp211=0.+tmp60;
REAL8 tmp213=1/tmp211;
REAL8 tmp208=0.+p->data[1];
REAL8 tmp209=tmp208*tmp48;
REAL8 tmp210=0.+tmp209;
REAL8 tmp217=-3.*eta;
REAL8 tmp219=1.*p->data[0];
REAL8 tmp220=0.+tmp219;
REAL8 tmp232=26.+tmp217;
REAL8 tmp233=2.*eta*tmp165*tmp232;
REAL8 tmp234=6.*eta*tmp153;
REAL8 tmp235=1.+tmp233+tmp234;
REAL8 tmp236=log(tmp235);
REAL8 tmp237=1.+tmp236;
REAL8 tmp238=tmp159*tmp159;
REAL8 tmp239=(x->data[0]*x->data[0]*x->data[0]*x->data[0]);
REAL8 tmp240=tmp202*tmp202;
REAL8 tmp241=tmp237*tmp238*tmp239*tmp240;
REAL8 tmp57=0.;
REAL8 tmp58=2.*tmp54*x->data[0];
REAL8 tmp59=tmp57+tmp58;
REAL8 tmp256=(x->data[0]*x->data[0]*x->data[0]);
REAL8 tmp262=eta*eta;
REAL8 tmp242=1./sqrt(tmp241);
REAL8 tmp243=1/tmp81;
REAL8 tmp244=sqrt(tmp241);
REAL8 tmp245=tmp243*tmp244;
REAL8 tmp246=-1.+tmp245;
REAL8 tmp247=-(tmp220*tmp242*tmp246*tmp81);
REAL8 tmp248=p->data[0]+tmp247;
REAL8 tmp249=1.*tmp248;
REAL8 tmp250=0.+tmp249;
REAL8 tmp251=tmp250*tmp250;
REAL8 tmp223=1.*tmp48;
REAL8 tmp224=0.+tmp223;
REAL8 tmp225=0.+p->data[2];
REAL8 tmp226=tmp224*tmp225;
REAL8 tmp227=0.+tmp226;
REAL8 tmp228=tmp227*tmp227;
REAL8 tmp229=1.*tmp213*tmp228*tmp60;
REAL8 tmp230=tmp210*tmp210;
REAL8 tmp231=1.*tmp206*tmp211*tmp230*tmp60;
REAL8 tmp252=1.*tmp159*tmp202*tmp213*tmp237*tmp251*tmp60;
REAL8 tmp269=pow(x->data[0],6.);
REAL8 tmp271=0.+tmp229+tmp231+tmp252;
REAL8 tmp290=sqrt(tmp211);
REAL8 tmp257=6.*sigmaKerr->data[2]*tmp206*tmp210*tmp211*tmp256*tmp48;
REAL8 tmp258=8.*sigmaStar->data[2]*tmp206*tmp210*tmp211*tmp256*tmp48;
REAL8 tmp259=tmp257+tmp258;
REAL8 tmp260=0.08333333333333333*eta*tmp259*tmp56;
REAL8 tmp261=-109.*eta;
REAL8 tmp263=51.*tmp262;
REAL8 tmp264=tmp261+tmp263;
REAL8 tmp265=8.*tmp206*tmp210*tmp211*tmp256*tmp264*tmp48;
REAL8 tmp266=-6.*eta;
REAL8 tmp267=39.*tmp262;
REAL8 tmp268=tmp266+tmp267;
REAL8 tmp270=-12.*tmp159*tmp202*tmp206*tmp210*tmp237*tmp251*tmp268*tmp269*tmp48;
REAL8 tmp272=-180.*eta*tmp206*tmp210*tmp211*tmp239*tmp271*tmp48;
REAL8 tmp273=tmp265+tmp270+tmp272;
REAL8 tmp274=0.006944444444444444*sigmaKerr->data[2]*tmp153*tmp273;
REAL8 tmp275=103.*eta;
REAL8 tmp276=-60.*tmp262;
REAL8 tmp277=tmp275+tmp276;
REAL8 tmp278=-4.*tmp206*tmp210*tmp211*tmp256*tmp277*tmp48;
REAL8 tmp279=-16.*eta;
REAL8 tmp280=21.*tmp262;
REAL8 tmp281=tmp279+tmp280;
REAL8 tmp282=-12.*tmp159*tmp202*tmp206*tmp210*tmp237*tmp251*tmp269*tmp281*tmp48;
REAL8 tmp283=3.*eta;
REAL8 tmp284=23.+tmp283;
REAL8 tmp285=-4.*eta*tmp206*tmp210*tmp211*tmp239*tmp271*tmp284*tmp48;
REAL8 tmp286=tmp278+tmp282+tmp285;
REAL8 tmp287=0.013888888888888888*sigmaStar->data[2]*tmp153*tmp286;
REAL8 tmp288=tmp260+tmp274+tmp287;
REAL8 tmp313=(1.0/(tmp211*tmp211));
REAL8 tmp314=tmp237*tmp237;
REAL8 tmp315=(tmp250*tmp250*tmp250*tmp250);
REAL8 tmp318=tmp271*tmp271;
REAL8 tmp291=tmp159*tmp202*tmp60;
REAL8 tmp292=sqrt(tmp291);
REAL8 tmp293=-tmp292;
REAL8 tmp294=tmp159*tmp202*tmp206*tmp211*tmp60;
REAL8 tmp295=sqrt(tmp294);
REAL8 tmp296=1.*tmp290*tmp295;
REAL8 tmp297=tmp293+tmp296;
REAL8 tmp298=1.+tmp229+tmp231+tmp252;
REAL8 tmp301=1.*coeffs->d1v2*eta*sigmaKerr->data[2]*tmp165;
REAL8 tmp302=-8.*sigmaKerr->data[2];
REAL8 tmp303=14.*sigmaStar->data[2];
REAL8 tmp304=-36.*sigmaKerr->data[2]*tmp159*tmp202*tmp213*tmp237*tmp251*tmp256;
REAL8 tmp305=-30.*sigmaStar->data[2]*tmp159*tmp202*tmp213*tmp237*tmp251*tmp256;
REAL8 tmp306=3.*sigmaKerr->data[2]*tmp271*x->data[0];
REAL8 tmp307=4.*sigmaStar->data[2]*tmp271*x->data[0];
REAL8 tmp308=tmp302+tmp303+tmp304+tmp305+tmp306+tmp307;
REAL8 tmp309=0.08333333333333333*eta*tmp308*tmp56;
REAL8 tmp310=27.*eta;
REAL8 tmp311=-353.+tmp310;
REAL8 tmp312=-2.*eta*tmp311;
REAL8 tmp316=360.*tmp238*tmp240*tmp262*tmp269*tmp313*tmp314*tmp315;
REAL8 tmp317=-2.*tmp271*tmp277*x->data[0];
REAL8 tmp319=-(eta*tmp284*tmp318*tmp60);
REAL8 tmp320=-47.*eta;
REAL8 tmp321=54.*tmp262;
REAL8 tmp322=tmp271*tmp281*x->data[0];
REAL8 tmp323=tmp320+tmp321+tmp322;
REAL8 tmp324=-6.*tmp159*tmp202*tmp213*tmp237*tmp251*tmp256*tmp323;
REAL8 tmp325=tmp312+tmp316+tmp317+tmp319+tmp324;
REAL8 tmp326=0.013888888888888888*sigmaStar->data[2]*tmp153*tmp325;
REAL8 tmp327=8.+tmp283;
REAL8 tmp328=-112.*eta*tmp327;
REAL8 tmp329=810.*tmp238*tmp240*tmp262*tmp269*tmp313*tmp314*tmp315;
REAL8 tmp330=4.*tmp264*tmp271*x->data[0];
REAL8 tmp331=-45.*eta*tmp318*tmp60;
REAL8 tmp332=16.*eta;
REAL8 tmp333=147.*tmp262;
REAL8 tmp334=tmp268*tmp271*x->data[0];
REAL8 tmp335=tmp332+tmp333+tmp334;
REAL8 tmp336=-6.*tmp159*tmp202*tmp213*tmp237*tmp251*tmp256*tmp335;
REAL8 tmp337=tmp328+tmp329+tmp330+tmp331+tmp336;
REAL8 tmp338=0.006944444444444444*sigmaKerr->data[2]*tmp153*tmp337;
REAL8 tmp339=0.+sigmaStar->data[2]+tmp301+tmp309+tmp326+tmp338;
REAL8 tmp299=1./sqrt(tmp298);
REAL8 tmp344=e3z*tmp339;
REAL8 tmp345=0.+tmp344;
REAL8 tmp342=(1.0/(tmp205*tmp205));
REAL8 tmp384=tmp211*tmp211;
REAL8 tmp381=sqrt(tmp298);
REAL8 tmp386=tmp224*tmp339;
REAL8 tmp387=0.+tmp386;
REAL8 tmp349=1./sqrt(tmp291);
REAL8 tmp350=tmp159*tmp202*tmp237*tmp60;
REAL8 tmp351=sqrt(tmp350);
REAL8 tmp352=1./sqrt(tmp294);
REAL8 tmp353=2.*tmp54;
REAL8 tmp354=0.;
REAL8 tmp355=0.+tmp353+tmp354;
REAL8 tmp356=tmp205*tmp355;
REAL8 tmp357=-4.*tmp81*x->data[0];
REAL8 tmp358=1/tmp196;
REAL8 tmp359=2.*coeffs->k2;
REAL8 tmp360=3.*coeffs->k3;
REAL8 tmp361=4.*coeffs->k4;
REAL8 tmp362=5.*tmp192*tmp56;
REAL8 tmp363=tmp361+tmp362;
REAL8 tmp364=1.*tmp363*tmp56;
REAL8 tmp365=tmp360+tmp364;
REAL8 tmp366=1.*tmp365*tmp56;
REAL8 tmp367=tmp359+tmp366;
REAL8 tmp368=1.*tmp367*tmp56;
REAL8 tmp369=coeffs->k1+tmp368;
REAL8 tmp370=-(eta*tmp159*tmp358*tmp369);
REAL8 tmp371=1.*tmp157;
REAL8 tmp372=1.*tmp53*tmp56;
REAL8 tmp373=tmp371+tmp372;
REAL8 tmp374=-2.*tmp202*tmp373;
REAL8 tmp375=2.*tmp159*tmp202*x->data[0];
REAL8 tmp376=tmp370+tmp374+tmp375;
REAL8 tmp377=1.*tmp376*tmp53;
REAL8 tmp378=tmp357+tmp377;
REAL8 tmp379=tmp378*tmp59;
REAL8 tmp380=tmp356+tmp379;
REAL8 tmp382=1.+tmp381;
REAL8 tmp390=1.+tmp229+tmp231+tmp252+tmp381;
REAL8 tmp400=1./sqrt(tmp211);
REAL8 tmp401=1./(tmp205*tmp205*tmp205);
REAL8 tmp343=(1.0/sqrt(tmp298*tmp298*tmp298));
REAL8 tmp383=1/tmp382;
REAL8 tmp404=1.*tmp159*tmp202*tmp206*tmp230*tmp239*tmp384*tmp387;
REAL8 tmp405=-(tmp159*tmp202*tmp237*tmp251*tmp387*tmp60);
REAL8 tmp406=tmp211*tmp387*tmp390;
REAL8 tmp407=0.+tmp405+tmp406;
REAL8 tmp408=1.*tmp159*tmp202*tmp407*tmp60;
REAL8 tmp409=0.+tmp404+tmp408;
REAL8 tmp212=1/tmp159;
REAL8 tmp214=1/tmp202;
REAL8 tmp341=sqrt(tmp211*tmp211*tmp211);
REAL8 tmp413=-2.*tmp159*tmp202*tmp60;
REAL8 tmp414=tmp351*tmp376;
REAL8 tmp415=tmp413+tmp414;
REAL8 tmp419=1.*tmp213*x->data[0];
REAL8 tmp420=-4.*tmp159*tmp202*tmp256;
REAL8 tmp421=tmp376*tmp81;
REAL8 tmp422=tmp420+tmp421;
REAL8 tmp423=0.5*tmp153*tmp206*tmp212*tmp214*tmp422*tmp81;
REAL8 tmp424=tmp419+tmp423;
REAL8 tmp425=2.*tmp381;
REAL8 tmp426=1.+tmp425;
REAL8 tmp392=2.*tmp206*tmp210*tmp211*tmp48*tmp60;
REAL8 tmp393=1.*tmp206*tmp210*tmp211*tmp299*tmp48*tmp60;
REAL8 tmp394=tmp392+tmp393;
REAL8 tmp215=tmp153*tmp205*tmp212*tmp213*tmp214;
REAL8 tmp216=1./sqrt(tmp215);
REAL8 tmp218=4.+tmp217;
REAL8 tmp221=(tmp220*tmp220*tmp220*tmp220);
REAL8 tmp222=2.*eta*tmp153*tmp218*tmp221;
REAL8 tmp253=1.+tmp222+tmp229+tmp231+tmp252;
REAL8 tmp348=(1.0/sqrt(tmp211*tmp211*tmp211));
REAL8 tmp412=1/tmp390;
REAL8 tmp435=-0.5*tmp210*tmp242*tmp290*tmp295*tmp382*tmp387*tmp415*x->data[0];
REAL8 tmp436=1.*tmp210*tmp290*tmp295*tmp387*tmp424*tmp426*x->data[0];
REAL8 tmp437=0.+tmp436;
REAL8 tmp438=tmp292*tmp437;
REAL8 tmp439=tmp435+tmp438;
REAL8 tmp440=tmp351*tmp439;
REAL8 tmp441=0.+tmp440;
REAL8 dHdp1=(1.*eta*(-(tmp165*tmp288*tmp339)-tmp230*tmp256*tmp297*tmp341*tmp342*tmp343*tmp345*tmp48+1.*e3z*tmp206*tmp288*tmp59-0.5*tmp210*tmp343*tmp349*tmp351*tmp352*tmp380*tmp383*tmp400*tmp401*tmp409*tmp48*tmp60+0.5*tmp299*tmp342*tmp348*tmp349*tmp351*tmp352*tmp380*tmp383*(1.*tmp159*tmp202*tmp206*tmp224*tmp230*tmp239*tmp288*tmp384+2.*tmp159*tmp202*tmp206*tmp210*tmp239*tmp384*tmp387*tmp48+1.*tmp159*tmp202*tmp60*(tmp211*tmp224*tmp288*tmp390+tmp211*tmp387*tmp394-tmp159*tmp202*tmp224*tmp237*tmp251*tmp288*tmp60))+1.*e3z*tmp206*tmp210*tmp288*tmp290*tmp297*tmp299*x->data[0]+1.*tmp206*tmp290*tmp297*tmp299*tmp345*tmp48*x->data[0]+1.*tmp206*tmp48*tmp59*x->data[0]+1.*tmp153*tmp212*tmp213*tmp214*tmp295*tmp351*tmp412*(-0.5*tmp206*tmp230*tmp242*tmp256*tmp295*tmp299*tmp341*tmp387*tmp415*tmp48-0.5*tmp210*tmp224*tmp242*tmp288*tmp290*tmp295*tmp382*tmp415*x->data[0]-0.5*tmp242*tmp290*tmp295*tmp382*tmp387*tmp415*tmp48*x->data[0]+tmp292*(2.*tmp206*tmp230*tmp256*tmp295*tmp299*tmp341*tmp387*tmp424*tmp48+1.*tmp210*tmp224*tmp288*tmp290*tmp295*tmp424*tmp426*x->data[0]+1.*tmp290*tmp295*tmp387*tmp424*tmp426*tmp48*x->data[0]))-(0.5*tmp210*tmp349*tmp351*tmp352*tmp380*tmp400*tmp401*tmp409*tmp48*tmp60*(1.0/(tmp382*tmp382)))/tmp298-tmp153*tmp212*tmp213*tmp214*tmp295*tmp394*tmp441*(1.0/(tmp390*tmp390))+(1.*tmp206*tmp210*tmp211*tmp216*tmp48*tmp60)/sqrt(tmp253)))/sqrt(1.+2.*eta*(-1.+0.5*tmp299*tmp342*tmp348*tmp349*tmp351*tmp352*tmp380*tmp383*tmp409+1.*tmp153*tmp212*tmp213*tmp214*tmp295*tmp412*tmp441+1.*tmp206*tmp345*tmp59+1.*tmp206*tmp210*tmp290*tmp297*tmp299*tmp345*x->data[0]+1.*tmp206*tmp210*tmp59*x->data[0]+1.*coeffs->dheffSSv2*eta*tmp161*(s1Vec->data[2]*s1Vec->data[2]+s2Vec->data[2]*s2Vec->data[2])-0.5*tmp165*(0.+tmp339*tmp339)+tmp216*sqrt(tmp253)));