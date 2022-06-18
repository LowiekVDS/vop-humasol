import { CircularProgress } from "@mui/material";
import { useEffect, useState } from "react";
import { FormattedMessage } from "react-intl";
import AdvancedOptions, {
  AdvancedOptionsData,
} from "../components/configuration/AdvancedOptions";
import RequiredOptions, {
  RequiredOptionsData,
} from "../components/configuration/RequiredOptions";
import TestingConnection from "../components/configuration/TestingConnection";
import ApiService from "../service/ApiService";

export enum ConfigSteps {
  REQUIRED_OPTIONS = 0,
  ADVANCED_OPTIONS = 1,
  DONE = 2,
  //TESTING = 2,
}

export default function Configure() {
  const [loading, setLoading] = useState<boolean>(true);

  const [configStep, setConfigStep] = useState<ConfigSteps>(
    ConfigSteps.REQUIRED_OPTIONS
  );

  const [requiredOptions, setRequiredOptions] = useState<RequiredOptionsData>(
    {}
  );
  const [advancedOptions, setAdvancedOptions] = useState<AdvancedOptionsData>(
    {}
  );

  const handleNextRequiredOptions = (data: RequiredOptionsData) => {
    setRequiredOptions(data);
    setConfigStep(configStep + 1);
  };

  const handleNextAdvancedOptions = (data: AdvancedOptionsData) => {
    setAdvancedOptions(data);
    setLoading(true);
    ApiService.fetch("/config", "PATCH", {
      type: requiredOptions.type,
      password: requiredOptions.password,
      txPower: data.txPower,
      LoRaSpreadFactor: data.LoRaSpreadFactor,
      bandwidth: data.bandwidth,
      crc: false,
      codingRate: 5,

      controllerPinPump: 32,
      controllerSafetymodeInitTimeout: 60000,
      controllerSafetymodePumpingPeriod: 60000,
      controllerSafetymodeRestingPeriod: 360000,
      controllerInvert: false,

      dispatcherSendInterval: 2000,
      dispatcherPinFloatswitch: 26,
      dispatcherInvert: false,
    }).then((r) => {
      setConfigStep(configStep + 1);
      setLoading(false);
    });
  };

  useEffect(() => {
    setRequiredOptions({
      type: "contr",
      password: "Qwerty@123",
      distance: 400,
      LoS: true,
    });
    setAdvancedOptions({
      txPower: 18,
      LoRaSpreadFactor: 10,
      bandwidth: 125000,
    });
    setLoading(false);
    // setLoading(true);
    // ApiService.fetch("/config", "GET").then((config) => {
    //   setRequiredOptions({
    //     type: config.type,
    //     password: config.password,
    //     distance: config.distance,
    //     LoS: config.LoS,
    //   });
    //   setAdvancedOptions({
    //     txPower: config.txPower,
    //     LoRaSpreadFactor: config.LoRaSpreadFactor,
    //     bandwidth: config.bandwidth,
    //   });
    //   setLoading(false);
    // });
  }, []);

  return (
    <>
      <h1 className="text-4xl font-bold">
        <FormattedMessage
          id={"Node configuration"}
          defaultMessage={"Node configuration"}
        />
      </h1>

      <p className="mt-4">
        <FormattedMessage
          defaultMessage={
            "Please follow the steps below to configure this node."
          }
          id={"welcomeconfig"}
        />
      </p>

      {loading && (
        <>
          <div className="grid gap-4 mt-4 items-left text-left mx-auto">
            <CircularProgress color="warning" />
          </div>
        </>
      )}

      {!loading &&
        {
          [ConfigSteps.REQUIRED_OPTIONS]: (
            <RequiredOptions
              data={requiredOptions}
              onContinue={handleNextRequiredOptions}
            />
          ),
          [ConfigSteps.ADVANCED_OPTIONS]: (
            <>
              <AdvancedOptions
                data={advancedOptions}
                onContinue={handleNextAdvancedOptions}
              />
              <a
                onClick={() => setConfigStep(configStep - 1)}
                className="hover:scale-105 transition-all mt-6 hover:text-blue-600 text-blue-400 font-bold underline"
              >
                <FormattedMessage defaultMessage={"Go back"} id={"Go back"} />
              </a>
            </>
          ),
          [ConfigSteps.DONE]: (
            <>
              <TestingConnection onContinue={() => { /* not empty */ }}/>
            </>
          ),
          // [ConfigSteps.TESTING]: <RequiredOptions />,
        }[configStep]}

      <a
        href="/"
        className="hover:scale-105 transition-all mt-6 hover:text-red-600 text-red-400 font-bold underline"
      >
        <FormattedMessage defaultMessage={"Cancel"} id={"Cancel"} />
      </a>
    </>
  );
}
